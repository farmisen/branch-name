open Js.Promise;
open Belt.Result;
open Banner;

let onOk = (~id, ~projectConfig, ~server) => {
  (
    switch ((server: Config.server)) {
    | Clubhouse(authToken) => Clubhouse.getStoryName(~id, ~authToken)
    | Jira(host, username, password) =>
      Jira.getStoryName(~id, ~host, ~username, ~password)
    | Gitlab(host, token, projectId) =>
      Gitlab.getStoryName(~id, ~host, ~token, ~projectId)
    }
  )
  |> then_(maybeName => {
       switch (maybeName) {
       | Ok(name) =>
         let branchName = Name.make(~id, ~name, ~config=projectConfig);
         Js.log(branchName);
         resolve(Ok());
       | Error(message) =>
         show(Some(message));
         resolve(Error());
       }
     })
  |> catch(_ => {
       show(Some("unknown failure"));
       resolve(Error());
     });
};

let onError = message => {
  show(Some(message));
  resolve(Error());
};

let onNamebranch = (~id, ~projectConfig) => {
  switch (Config.server(~projectConfig)) {
  | Ok(server) => onOk(~id, ~projectConfig, ~server)
  | Error(message) => onError(message)
  };
};

let onHelp = message => {
  show(message);
  resolve(Error());
};

let onDoc = () => {
  doc();
  resolve(Ok());
};

let cli = () => {
  switch (Args.parseArgs()) {
  | NameBranch(id, projectConfig) => onNamebranch(~id, ~projectConfig)
  | Help(message) => onHelp(message)
  | Doc => onDoc()
  };
};
