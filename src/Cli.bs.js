// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Args$BranchName = require("./Args.bs.js");
var Jira$BranchName = require("./Jira.bs.js");
var Name$BranchName = require("./Name.bs.js");
var Banner$BranchName = require("./Banner.bs.js");
var Config$BranchName = require("./Config.bs.js");
var Clubhouse$BranchName = require("./Clubhouse.bs.js");

function onOk(id, projectConfig, server) {
  var tmp;
  tmp = server.TAG ? Jira$BranchName.getStoryName(id, server._0, server._1, server._2) : Clubhouse$BranchName.getStoryName(id, server._0);
  return tmp.then(function (maybeName) {
                if (maybeName.TAG) {
                  Banner$BranchName.show(maybeName._0);
                  return Promise.resolve({
                              TAG: /* Error */1,
                              _0: undefined
                            });
                }
                var branchName = Name$BranchName.make(id, maybeName._0, projectConfig);
                console.log(branchName);
                return Promise.resolve({
                            TAG: /* Ok */0,
                            _0: undefined
                          });
              }).catch(function (param) {
              Banner$BranchName.show("unknown failure");
              return Promise.resolve({
                          TAG: /* Error */1,
                          _0: undefined
                        });
            });
}

function onError(message) {
  Banner$BranchName.show(message);
  return Promise.resolve({
              TAG: /* Error */1,
              _0: undefined
            });
}

function onNamebranch(id, projectConfig) {
  var server = Config$BranchName.server(projectConfig);
  if (server.TAG) {
    return onError(server._0);
  } else {
    return onOk(id, projectConfig, server._0);
  }
}

function onHelp(message) {
  Banner$BranchName.show(message);
  return Promise.resolve({
              TAG: /* Error */1,
              _0: undefined
            });
}

function onDoc(param) {
  Banner$BranchName.doc(undefined);
  return Promise.resolve({
              TAG: /* Ok */0,
              _0: undefined
            });
}

function cli(param) {
  var message = Args$BranchName.parseArgs(undefined);
  if (typeof message === "number") {
    Banner$BranchName.doc(undefined);
    return Promise.resolve({
                TAG: /* Ok */0,
                _0: undefined
              });
  }
  if (!message.TAG) {
    return onNamebranch(message._0, message._1);
  }
  Banner$BranchName.show(message._0);
  return Promise.resolve({
              TAG: /* Error */1,
              _0: undefined
            });
}

exports.onOk = onOk;
exports.onError = onError;
exports.onNamebranch = onNamebranch;
exports.onHelp = onHelp;
exports.onDoc = onDoc;
exports.cli = cli;
/* Args-BranchName Not a pure module */
