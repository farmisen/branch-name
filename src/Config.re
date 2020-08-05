[@bs.val] external home: string = "process.env.HOME";
open Belt.Result;

type server =
  | Clubhouse(string) // token
  | Jira(string, string, string) // host, username, token
  | Gitlab(string, string, string); // host, token, project id

type serverConfig = {
  host: option(string), // gitlab, jira
  username: option(string), // jira
  token: option(string), // gitlab, clubhouse, jira
  projectId: option(string) // gitlab
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
[@bs.module "./dynamicRequire"]
external dynReq: string => required = "default";
[@bs.val] external require: string => required = "require";
[@bs.get] external defaultExport: required => config = "default";

let loadModule = path => {
  dynReq(path) |> defaultExport;
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
    let {serverConfig: {host, username, token}} = projectConfig;
    switch (host, username, token) {
    | (Some(host), Some(username), Some(token)) =>
      Ok(Jira(host, username, token))
    | (Some(_), Some(_), None) => Error("server config missing token value")
    | (Some(_), None, Some(_)) =>
      Error("server config missing username value")
    | (Some(_), None, None) =>
      Error("server config missing username and token values")
    | (None, Some(_), Some(_)) => Error("server config missing host value")
    | (None, Some(_), None) =>
      Error("server config missing host and token values")
    | (None, None, Some(_)) =>
      Error("server config missing host and token values")
    | (None, None, None) =>
      Error("server config missing host, username and token values")
    };
  | "clubhouse" =>
    switch (projectConfig.serverConfig.token) {
    | Some(token) => Ok(Clubhouse(token))
    | None => Error("server config missing token value")
    }
  | "gitlab" =>
    let {serverConfig: {host, token, projectId}} = projectConfig;
    switch (host, token, projectId) {
    | (Some(host), Some(token), Some(projectId)) =>
      Ok(Gitlab(host, token, projectId))
    | (Some(_), Some(_), None) =>
      Error("server config missing projectId value")
    | (Some(_), None, Some(_)) => Error("server config missing token value")
    | (Some(_), None, None) =>
      Error("server config missing token and projectId values")
    | (None, Some(_), Some(_)) => Error("server config missing host value")
    | (None, Some(_), None) =>
      Error("server config missing host and projectId values")
    | (None, None, Some(_)) =>
      Error("server config missing host and projectId values")
    | (None, None, None) =>
      Error("server config missing host, token and projectId values")
    };
  | _ => Error("unsupported server type")
  };
