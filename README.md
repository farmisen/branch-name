# branch-name

A cli tool to generate well formatted pr names from your favorite issue trackers. So far Jira, Clubhouse and Gitlab are supported.


## Installation ##

```shell
$ yarn global add @farmisen/branch-name

```

## Usage ##

```
branch-name [options]

  Options:

    -p, --project  project defined in the config file
    -i, --id       issue identifier
    -c, --config   Config file location (default to $HOME/.branch-name)
    -h, --help     Output usage information
    -d, --doc      Output full documentation
```

## Examples ##
```
~/P/f/branch-name > branch-name --project coffee-bot --id 17382 
farmisen/ch17382/fix-filter-cleanup-cron-table

~/P/f/branch-name > branch-name --project simu --id SIMU-1659
SIMU-1659_performance_remove_unused_filters

~/P/f/branch-name > --project clemet --id 80
clem_80-retire_the_log_drawer


~/P/f/branch-name > cat ~/.branch-name                                               
var config = {
    projects: [
        {
            slug: "coffee-bot",
            server: "clubhouse",
            serverConfig: {
                authToken: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",
            },
            
            formatter: (id, title) => `farmisen/ch${id}/${title}`
        },
        {
            slug: "simu",
            server: "jira",
            serverConfig: {
                host: "xxxxxxxxxxxx.atlassian.net",
                username: "xxxxxxx@xxxxxxxxxx.xxx",
                password: "xxxxxxxxxxxxxxxxxxxxxxxx",
            },
            formatter: (id, title) => `${id}_${title}`,
            separator: "_"
        },
        {
            slug: "clemet",
            server: "gitlab",
            serverConfig: {
                host: "xxxxxxxxxxxx.xxxxxxxxx.xxx",
                token: "xxxxxxxxxxxxxxxxxxxxxxxx",
                projectId: 5,
            },
            formatter: (id, title) => `clem_${id}-${title}`,
            separator: "_"
        }
    ]
};
exports.default=config

```

## Documentation ##

### Config file

  The config file is a javascript file exporting a config object as default export:

  ```
  var config = {...}
  exports.default = config;
  ```

  #### Config object fields


| name     | type          | info                    |
|----------|---------------|-------------------------|
| projects | list(project) | list of project objects |


  #### Project object fields
  
| name         | type                                | info                                        |
|--------------|-------------------------------------|---------------------------------------------|
| slug         | string                              | project slug used with the --project option |
| server       | "clubhouse" \| "jira \| gitlab"     | type of issues tracking server              |
| serverConfig | object                              | server config object                        |
| formatter    | (id:string, title:string) => string | an optional branch name formatter           |
| sanitizer    | (title:string) => string            | an optional issue name sanitizer            |
| separator    | string                              | an optional word separator (default to "-") |

  #### Server config object fields

  ##### Jira:

| name     | type   | info                     |
|----------|--------|--------------------------|
| host     | url    | jira server host         |
| username | string | jira username            |
| password | string | jira personal auth token |
  
  ##### Clubhouse:

| name      | type   | info                     |
|-----------|--------|--------------------------|
| authToken | string | jira personal auth token |

##### Gitlab:

| name  | type   | info                       |
|-------|--------|----------------------------|
| host  | url    | gitlab server host         |
| token | string | gitlab personal auth token |


## Publishing

```
$ yarn clean
$ yarn build
$ npx webpack
$ npm publish --access public 
```

## Copyright & License

Copyright (c) 2020 Fabrice Armisen.

Distributed under the MIT License (see [LICENSE](./LICENSE)).
