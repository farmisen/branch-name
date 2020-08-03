var config = {
    projects: [
        {
            slug: "dk",
            server: "clubhouse",
            serverConfig: {
                authToken: "5f1f1b64-685c-4a3b-a08b-6b57206f9213",
            },
            
            formatter: (id, title) => `farmisen/ch${id}/${title}`
        },
        {
            slug: "prom",
            server: "jira",
            serverConfig: {
                host: "coderefactory.atlassian.net",
                username: "fab@coderefactory.com",
                password: "uhcPuDqFmPnur2BjdxZpAD83",
            },
            formatter: (id, title) => `${id}_${title}`,
            separator: "_"
        }
    ]
};
exports.default = config;
