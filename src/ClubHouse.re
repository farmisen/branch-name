// import Clubhouse from 'clubhouse-lib';
// const client = Clubhouse.create('your token value'); // See https://github.com/clubhouse/clubhouse-lib#how-to-get-an-api-token
// module Await = {
//   let let_ = Promise.flatMap;

//   // This is totally optional. It can be nice sometimes to return a
//   // non-promise value at the end of a function and have it automatically
//   // wrapped. See example inside the Some branch of the switch below.
//   module Wrap = {
//     let let_ = Promise.map;
//   };
// };

module Bindings = {
  type t;
  [@bs.module "clubhouse-lib"] external clubhouse: t = "default";
  type client;
  [@bs.send] external create: (t, string) => client = "create";
  let create = (token: string) => create(clubhouse, token);
  type story;
  [@bs.send]
  external getStory: (client, string) => Js.Promise.t(story) = "getStory";
  let getStory: (client, string) => Js.Promise.t(story) =
    (client: client, id: string) => getStory(client, id);
  [@bs.get] external name: story => string;
};

let getStoryName = (~id: string, ~config: Config.project) => {
  let client =
    switch (config.authToken) {
    | Some(token) => Bindings.create(token)
    | None => failwith("Missing authToken")
    };
  Bindings.getStory(client, id)
  |> Js.Promise.then_(story => {Js.Promise.resolve(Bindings.name(story))});
};
