[@bs.val] external home: string = "process.env.HOME";
open Belt.Result;

type server =
  | Clubhouse(string) // authtoken
  | Jira(string, string, string);

type serverConfig = {
  // jira
  host: option(string),
  username: option(string),
  password: option(string),
  // clubhouse
  authToken: option(string),
};

type projectConfig = {
  slug: string,
  server: string,
  serverConfig,
  formatter: option((string, string) => string),
  sanitizer: option(string => string),
  separator: option(string),
};

type config = {projects: list(projectConfig)};

type required;
[@bs.val] external require: string => required = "require";
[@bs.get] external defaultExport: required => config = "default";

let loadModule = path => {
  require(path) |> defaultExport;
};

[@bs.get] external projects: config => array(projectConfig) = "projects";

let projectConfig = (~projectSlug: string, ~configPath: option(string)) => {
  let path = Belt.Option.getWithDefault(configPath, home ++ "/.branch-name");
  let config = loadModule(path);
  let projects = projects(config) |> Array.to_list;

  try(Ok(List.find(p => p.slug === projectSlug, projects))) {
  | _ => Error("unknown project " ++ projectSlug)
  };
};

let server = (~projectConfig: projectConfig) =>
  switch (projectConfig.server) {
  | "jira" =>
    let {serverConfig: {host, username, password}} = projectConfig;
    switch (host, username, password) {
    | (Some(host), Some(username), Some(password)) =>
      Ok(Jira(host, username, password))
    | (Some(_), Some(_), None) =>
      Error("server config missing password value")
    | (Some(_), None, Some(_)) =>
      Error("server config missing username value")
    | (Some(_), None, None) =>
      Error("server config missing username and password values")
    | (None, Some(_), Some(_)) => Error("server config missing host value")
    | (None, Some(_), None) =>
      Error("server config missing host and password values")
    | (None, None, Some(_)) =>
      Error("server config missing host and password values")
    | (None, None, None) =>
      Error("server config missing host, username and password values")
    };
  | "clubhouse" =>
    switch (projectConfig.serverConfig.authToken) {
    | Some(authToken) => Ok(Clubhouse(authToken))
    | None => Error("server config missing authToken value")
    }
  | _ => Error("unsupported server type")
  };
