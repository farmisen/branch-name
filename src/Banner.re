let show = (message: option(string)) => {
  switch (message) {
  | Some(message) => Js.log("Error: " ++ message)
  | None => ()
  };

  Js.log(
    {|
Usage: branch-name [options]

  Options:

    -p, --project  project defined in the config file
    -i, --id       issue identifier
    -c, --config   Config file location (default to $HOME/.branch-name)
    -h, --help     Output usage information
    -d, --doc      Output full documentation
    |},
  );
};

let doc = () => {
  show(None);
  Js.log(
    {|

  Config file
  ===========

  The config file is a javascript file exporting a config object as default export:

  var config = {...}
  exports.default = config;


  Config object
  -------------

  {
    projects:                                             list of project objects
  }


  Project object
  --------------

  {
    slug: string,                                       project slug
    server: "clubhouse" | "jira",                       type of server,
    serverConfig: object,                               server config object
    formatter: (id:string, title:string) => string,     an optional branch name formatter
    sanitizer: (title:string) => string,                an optional issue name sanitizer
    separator: string                                   an optional word separator (default to "-")
  }


  Server config object
  --------------------

  Jira:

  {
    host: url,                                          jira server host
    username: string,                                   jira username
    password: string,                                   jira personal auth token
  }

  Clubhouse:

  {
    authToken: string,                                  clubhouse personal auth token
  }

    |},
  );
};
