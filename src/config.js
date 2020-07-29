"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var config = {
    projects: [
        {
            slug: "dk",
            server: "clubhouse",
            authToken: "5f1f1b64-685c-4a3b-a08b-6b57206f9213",
            transformer: (id, title) => `farmisen/ch${id}/${title}`
        }
    ]
};
exports.default = config;