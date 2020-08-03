exports.default = function(path) {
    path = path.split('\\').join('/');
    return eval(`require('${path}');`);
  }