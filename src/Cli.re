[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

let clubhouse = (~id, ~config) => {
  ClubHouse.getStoryName(~id, ~config)
  |> Js.Promise.then_(name => {
       let branchName = NameFactory.make(~id, ~name, ~config);
       Js.log(branchName);

       Js.Promise.resolve();
     });
};

let cli = () => {
  switch (Args.parseArgs()) {
  | NameBranch(id, projectConfig) =>
    let server = projectConfig.server;
    switch (server) {
    | "jira" => Js.log("NameBranch for jira")
    | "clubhouse" => ignore(clubhouse(~id, ~config=projectConfig))
    | _ => failwith(server ++ " not supported.")
    };
  | ListProjects => Js.log("ListProjects")
  | CreateProject => Js.log("CreateProject")
  };
};
