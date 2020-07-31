open String;
open Js.String;
open Belt.Option;

let defaultformatter = (id, name) => {
  id ++ "-" ++ name;
};

let defaultSanitizer = title =>
  title
  |> lowercase_ascii
  |> replaceByRe([%re "/[\s:\/\[\]{}()_\"]/g"], "-")
  |> replaceByRe([%re "/--*/g"], "-");

let withDefault = (value, default) => value->mapWithDefault(default, x => x);

let make = (~id, ~name, ~config: Config.projectConfig) =>
  name
  |> config.sanitizer->withDefault(defaultSanitizer)
  |> replaceByRe([%re "/-/g"], config.separator->withDefault("-"))
  |> config.formatter->withDefault(defaultformatter, id);
