[@bs.module] external arg: 'a => Js.t('a) = "arg";

open Belt.Result;

type actions =
  | NameBranch(string, Config.projectConfig)
  | Help(option(string))
  | Doc;

let parseArgs = () => {
  let parameters = [%bs.raw
    {| {
    '--id': String,
    '--project': String,
    '--help': Boolean,
    '--doc': Boolean,
    '--config': String,
    '-i': '--id',
    '-p': '--project',
    '-h': '--help',
    '-d': '--doc'
} |}
  ];

  let parsed = arg(parameters);
  if (Belt.Option.getWithDefault(parsed##"--doc", false)) {
    Doc;
  } else {
    switch (parsed##"--id", parsed##"--project") {
    | (None, None) => Help(None)
    | (None, _) => Help(Some("Missing project"))
    | (_, None) => Help(Some("Missing issue id"))
    | (Some(id), Some(project)) =>
      let config =
        Config.projectConfig(
          ~projectSlug=project,
          ~configPath=parsed##"--config",
        );
      switch (config) {
      | Ok(projectConfig) => NameBranch(id, projectConfig)
      | Error(msg) => Help(Some(msg))
      };
    };
  };
};
