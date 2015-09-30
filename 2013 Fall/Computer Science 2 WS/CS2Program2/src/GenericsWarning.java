// Sean Szumlanski
// COP 3503, Fall 2013

// GenericsWarning.java
// ====================
// This little beast should generate warnings when you try to compile it. If you
// can compile this without receiving any warnings from your compiler/IDE, we
// need to get you into an environment where you're getting Xlint warnings about
// unchecked or unsafe operations.


import java.util.*;

public class GenericsWarning<QQ> {
	LinkedList<String> L;

	GenericsWarning() {
		L = new LinkedList();
		L.add(null);
	}
}
