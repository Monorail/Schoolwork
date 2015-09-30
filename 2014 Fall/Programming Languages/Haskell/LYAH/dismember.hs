dismember lst =
	let first = head lst
	in let rest = tail lst
		in (lst, first:rest)