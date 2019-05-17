#include "hof.h"

int load(struct player list[]){
	FILE *fp = fopen(HOF_FILE, "r+");
	if(fp == NULL)
		return -1;
	int i = 0, n = 0;
	while(!feof(fp) && i < 10) {
		fscanf(fp, "%s%d", list[i].name, &list[i].score);
		n++;
		i++;
	}
	if(list[0].score == 0)
		n = 0;
	fclose(fp);
	return n;
}

bool save(const struct player list[], const int size){
	FILE *fp = fopen(HOF_FILE, "w");
	if(fp == NULL)
		return false;
	for(int i = 0; i < size; i++){
		fprintf(fp, "%s %d", list[i].name, list[i].score);
		if(i != size -1)
			fprintf(fp, "\n");
	}
	return true;
}

bool add_player(struct player list[], int* size, const struct player player){
	printf("%d\n", *size);
	size_t structs_len = (size_t) *size;
	if(structs_len != 0)
		qsort(list, structs_len, sizeof(struct player), cmp_by_score);
	int hof = player.score;
	if(player.score < list[*size-1].score && *size == 10){
		return false;
	} else if(*size < 10) {
		strcpy(list[*size].name, player.name);
		list[*size].score = player.score;
		if(*size != 0)
			qsort(list, ++structs_len, sizeof(struct player), cmp_by_score);
		++(*size);
	} else {
		strcpy(list[*size-1].name, player.name);
		list[*size-1].score = player.score;
		qsort(list, structs_len, sizeof(struct player), cmp_by_score);
	}
	save(list, *size);
	return true;	
}

int cmp_by_score(const void *a, const void *b){
	struct player *ia = (struct player *)a;
	struct player *ib = (struct player *)b;

	return (ib->score - ia->score);
}