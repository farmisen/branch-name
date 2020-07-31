module Bindings = {
  type t;
  [@bs.module "clubhouse-lib"] external clubhouse: t = "default";

  type client;
  [@bs.send] external create: (t, string) => client = "create";
  let create = token => create(clubhouse, token);

  type story;
  [@bs.send]
  external getStory: (client, string) => Js.Promise.t(story) = "getStory";
  let getStory = (id, client) => getStory(client, id);
  [@bs.get] external name: story => string = "name";
};

open Bindings;
open Js.Promise;
open Belt.Result;

let getStoryName = (~id: string, ~authToken: string) => {
  authToken
  |> create
  |> getStory(id)
  |> then_(story => {resolve(Ok(name(story)))})
  |> catch(_err => {resolve(Error("failed while fetching the story"))});
};
