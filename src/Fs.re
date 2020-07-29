type options = {
  encoding: string,
  flag: string,
};

[@bs.module "fs"]
external readFileSync:
  (~path: string, ~options: options=?) => Js.Nullable.t(string) =
  "readFileSync";

[@bs.module "fs"] external existsSync: (~path: string) => bool = "existsSync";

let readSync = (~path: string, ~encoding: string, ~flag: string) => {
  let res = readFileSync(~path, ~options={encoding, flag});
  Js.Nullable.toOption(res);
};
