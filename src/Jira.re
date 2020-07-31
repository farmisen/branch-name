module Bindings = {
  type config = {
    protocol: string,
    host: string,
    username: string,
    password: string,
    strictSSL: bool,
  };

  type client;
  [@bs.module] [@bs.new] external jiraApi: config => client = "jira-client";
  type fields = {summary: string};
  type issue = {fields};

  [@bs.send]
  external findIssue: (client, string) => Js.Promise.t(issue) = "findIssue";
  let findIssue = (id, client) => findIssue(client, id);

  [@bs.get] external fields: issue => fields = "fields";
  [@bs.get] external summary: fields => string = "summary";
};

open Bindings;
open Js.Promise;
open Belt.Result;

let getStoryName = (~id, ~host, ~username, ~password) => {
  jiraApi({protocol: "https", host, username, password, strictSSL: true})
  |> findIssue(id)
  |> then_(issue => {resolve(Ok(issue |> fields |> summary))})
  |> catch(_err => {resolve(Error("failed while fetching the story"))});
};
