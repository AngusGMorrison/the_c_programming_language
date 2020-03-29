/**
 * Add a field-handling capability, so sorting may be done on fields within
 * lines, each field sorted according to an independent set of options. (The
 * index for this book was sorted with -df for the index category and -n for
 * the page numbers).
 * 
 * To my mind, the question doesn't provide enough detail to effect a solution,
 * or indeed produce a good, general-purpose program. Underlining this is the
 * fact that the official solution book does not allow multiple fields within
 * lines, nor "each field sorted according to an independent set of options".
 * In the official solution, you sort either on a whole line, or by a single
 * field within the line, which is not what the question asks.
 * 
 * The example the question gives is particularly unclear: "The index for this
 * book was sorted with -df for the index category, and -n for the page
 * numbers". An example index entry is "keyboard input 51, 151, 170". Even if
 * a field were provided that could account for an unknown length of page
 * numbers ahead of time there would be no way of knowing how best to split the
 * string "51, 151, 170" into a sortable array of substrings.
 * 
 * Even if you made the assumption to split when isdigit(c) == false, what if
 * the user had not specified a series of numbers, but a field of letters
 * they hoped to sort alphabetically?
 * 
 * There is no general-purpose solution that makes sense given the construction
 * of the question, and no correct official solution exists.
 */ 