public class Book {
	private String title, author, tableOfContents = "";
	private int nextPage = 1;

	public Book(String title, String author) {
		this.title = title;
		this.author = author;
	}

	public String toString() {

		return title + "\n" + author;

	}

	public void addChapter(String chapter, int pages) {
		tableOfContents += "\n" + chapter + "..." +pages;
	}

	public int getPages() {
		return nextPage;
	}
	public String getTableOfContents(){
		int[][] plan = {{8,20,50},{12,30,75}};
		return tableOfContents;
	}
}