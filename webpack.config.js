const nodeExternals = require('webpack-node-externals');

module.exports = {
    entry: {
      main: './src/Cli.bs.js'
    },
    target: 'node',
    mode: 'development',
    output: {
        libraryTarget: 'commonjs'
    },
    externals: [nodeExternals({allowlist:[/bs-platform/]})],
  };