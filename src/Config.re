[@bs.val] external home: string = "process.env.HOME";

//
// Types
//

type project = {
  slug: string,
  server: string,
  authToken: option(string),
  transformer: option((string, string) => string),
  sanitizer: option(string => string),
};

type config = {projects: list(project)};

//
// config file
//

[@bs.module "./config.js"] external config: config = "default";
[@bs.get] external projects: config => array(project);

let projects = projects(config) |> Array.to_list;

let projectConfig = (~projectSlug: string) =>
  try(Some(List.find(p => p.slug === projectSlug, projects))) {
  | _ => None
  };
