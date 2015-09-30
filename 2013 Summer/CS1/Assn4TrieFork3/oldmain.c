
int main(int argc, char **argv){
	//INSERTSTRING CANNOT TAKE LITERALS
	TrieNode *root  = createTrieNode();
	TrieNode *temp;
	FILE* ifp;
	int numWords;
	int i = 0;
	char *str = malloc(sizeof(char)*1023);
	if(argc<2){
		printf("Not enough args!\n");
		if (debug != 1 ) return 0;
	}
		
	ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		fprintf(stderr, "Can't open str file in.list!\n");
	}
	numWords=0;
	char **sentence=malloc(sizeof(char *)*(NUMWORDS+1));
	for(i =0;i<NUMWORDS;i++){
		sentence[i] = malloc(sizeof(char) * (NUMCHARS+1));
	}
	//inserts sentence into the root trie, should insert all
	i=0;
	do{
		fscanf(ifp,"%s",str);
		strcpy(sentence[i],str);
		i++;
	}while(strcmp(str,".") !=0);
	
	if(MAINDEBUG)printf("main(): Start insertSentence()\n");
	insertSentence(root, sentence);
	printTrie(root,1);
	root->subtrie=createTrieNode();
	if(MAINDEBUG)printTrie(root, 1);
	TrieNode *replHolder = getNode(root, "spin");
	if(MAINDEBUG)printf("main(): Got past insertSentence()\nmain(): Starting updateSubtrie()\n");
	if(MAINDEBUG)printf("%d\n",--i);
	updateSubtrie(root,sentence[0],sentence,i);
	if(MAINDEBUG)printf("main(): Printing subtrie:\n");
	printTrie(root->subtrie,1);
	////////////////////////////////////////////////////////
	i=0;
	do{
		fscanf(ifp,"%s",str);
		strcpy(sentence[i],str);
		i++;
	}while(strcmp(str,".") !=0);
	
	if(MAINDEBUG)printf("main(): Start insertSentence()\n");
	root=insertSentence(root, sentence);
	printTrie(root,1);
	root->subtrie=createTrieNode();
	if(MAINDEBUG)printTrie(root, 1);
	replHolder = getNode(root, "spin");
	if(MAINDEBUG)printf("main(): Got past insertSentence()\nmain(): Starting updateSubtrie()\n");
	if(MAINDEBUG)printf("%d\n",--i);
	updateSubtrie(root,sentence[0],sentence,i);
	if(MAINDEBUG)printf("main(): Printing subtrie:\n");
	printTrie(root->subtrie,1);
	if(MAINDEBUG)printf("main(): Printing maintrie:\n");
	printTrie(root,1);
	
	
	//the trie should be done by this line
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	if(MAINDEBUG)printf("Main(): Herp\n");
	ifp = fopen(argv[2], "r");
	if(MAINDEBUG)printf("Main(): %s opened\n",argv[2]);
	while(fscanf(ifp, "%s", str)!=EOF){
		if(MAINDEBUG)printf("Main(): Parsing cmd %s\n",str);
		if(strcmp(str,"!") == 0){
			if(MAINDEBUG)printf("main(): Printing trie\n");
			printTrie(root,0);	
		}else{
			printf("%s\n",str);
			lowerString(str);
			int seenWord = 0;
			if(MAINDEBUG)printf("\nLooking for %s inside of \n",str);
			if(MAINDEBUG)printTrie(root,0);
			if(MAINDEBUG)printf("Main(): Getting subtrie\n");
			TrieNode *h = getNode(root,str);
			if(h==NULL){
				printf("(INVALID STRING)\n");
				continue;
			}
			h = h->subtrie;
			if(MAINDEBUG)printf("Main(): Got subtrie\n");
			printTrie(h,1);
		}
	}
	
	return 0;
}
