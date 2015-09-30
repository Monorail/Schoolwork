module Iconify where
import WindowLayout

-- iconify :: WindowLayout -> WindowLayout
-- iconify Window x y z = Window x 2 2 
-- iconify Horizontal x y z = Window x 2 2 

iconify :: WindowLayout -> WindowLayout 
iconify (Window n _ _) 	= (Window n 2 2)
iconify (Horizontal list) = Horizontal (map iconify list)
iconify (Vertical list) = Vertical (map iconify list)










-- iconify :: WindowLayout -> WindowLayout 
-- iconify (Window n _ _) = (Window n 2 2)
-- iconify (Horizontal list) = iconify (Horizontal (tail list))
-- iconify (Vertical list) = Vertical [iconify (head list)]
