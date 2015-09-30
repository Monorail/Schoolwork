module ChangeChannel where
import WindowLayout

changeChannel :: String -> String -> WindowLayout -> WindowLayout
changeChannel new old (Window name x y)
	| name == old	= (Window new x y)
	| otherwise 	= (Window name x y)
changeChannel new old (Horizontal list) = Horizontal (map (changeChannel new old) list)
changeChannel new old (Vertical list) = Vertical (map (changeChannel new old) list)