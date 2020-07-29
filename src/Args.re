[@bs.module] external arg: 'a => Js.t('a) = "arg";

type actions =
  | NameBranch(string, Config.project)
  | ListProjects
  | CreateProject;

let parseArgs = () => {
  let parameters = [%bs.raw
    {| {
    '--id': String,
    '--project': String,
    '--list': Boolean,
    '--create': Boolean,
    '-i': '--id',
    '-p': '--project'
} |}
  ];

  let result = arg(parameters);
  if (result##"--list") {
    ListProjects;
  } else if (result##"--create") {
    CreateProject;
  } else {
    let config = Config.projectConfig(~projectSlug=result##"--project");
    let projectConfig =
      switch (config) {
      | Some(config) => config
      | _ => failwith("Error reading the project config")
      };
    NameBranch(result##"--id", projectConfig);
  };
};
