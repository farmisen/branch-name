module Bindings = {
  type config = {
    host: string,
    token: string,
  };

  type client;
  [@bs.module "@gitbeaker/node"] external gitlab: config => client = "Gitlab";
  type issues;
  [@bs.get] external issues: client => issues = "Issues";

  type issue;
  [@bs.send]
  external findIssue: (issues, string, string) => Js.Promise.t(issue) =
    "show";
  let findIssue = (projectId, id, client) =>
    findIssue(client, projectId, id);

  [@bs.get] external title: issue => string = "title";
};

open Bindings;
open Js.Promise;
open Belt.Result;

let getStoryName = (~id, ~host, ~token, ~projectId) =>
  gitlab({host, token})
  |> issues
  |> findIssue(projectId, id)
  |> then_(issue => {resolve(Ok(issue |> title))})
  |> catch(_err => {resolve(Error("failed while fetching the story"))});
