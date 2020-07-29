let defaultTransformer = (id, name) => {
  id ++ "-" ++ name;
};

let defaultSanitizer = title => {
  title
  |> String.lowercase
  |> Js.String.replaceByRe([%re "/[\s:\/\[\]{}()\"]/g"], "-")
  |> Js.String.replaceByRe([%re "/--*/g"], "-");
};

let make = (~id, ~name, ~config: Config.project) => {
  let pattern =
    switch (config.transformer) {
    | Some(transformer) => transformer
    | None => defaultTransformer
    };
  let sanitizer =
    switch (config.sanitizer) {
    | Some(sanitizer) => sanitizer
    | None => defaultSanitizer
    };
  name |> sanitizer |> pattern(id);
};
