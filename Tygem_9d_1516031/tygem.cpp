#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Err "Kifu2014.index" line 175013, "Kifu/2014-11" line 12814, 751137541 is strange.
const int MAX_ONE_LINE = 256;
const int MAX_ONE_SGF = 256*16;

int sgf_n = 0;
int year = 0;
FILE *fp_sgf = NULL;

void fgets_sgf(char *one_sgf, int max_buf)
{
	for (;;) {
		if ( fp_sgf == NULL ) {
			char ss[256];
			int month = sgf_n + 1;
			if ( year == 2005 ) month  = sgf_n + 11;
			if ( month > 12 ) { printf("month > 12 err\n"); exit(0); }
			sprintf(ss,"Kifu/%d-%02d",year,month);
			fp_sgf = fopen(ss,"r");
			if ( fp_sgf==NULL ) { printf("fopen sgf err\n"); exit(0); }
		}
		if ( fgets( one_sgf, max_buf, fp_sgf ) != NULL ) break;
		printf("EOF sgf_n=%d\n",sgf_n);
		sgf_n++;
		fclose(fp_sgf);
		fp_sgf = NULL;
	}
}

int main(int argc, char *argv[])
{
	if ( argc != 2 ) { printf("usage:\n\n./tygem 2005\n\n"); exit(0); }
	year = atoi(argv[1]);

	char si[256];
	sprintf(si,"index/Kifu%d.index",year);

	FILE *fp = fopen(si,"r");
	if ( fp==NULL ) { printf("fopen err\n"); exit(0); }

	int lines = 0;
	for (;;) {
		char one_line[MAX_ONE_LINE];
		if ( fgets( one_line, MAX_ONE_LINE, fp ) == NULL ) { printf("EOF?\n"); break; }
		int n = strlen(one_line);
		int i;
		for (i=0;i<n;i++) {
			if ( one_line[i] < 0 ) one_line[i] = 'x';
		}
//		printf("%s",one_line);
		char id[MAX_ONE_LINE];
		char date[MAX_ONE_LINE];
		char hm[MAX_ONE_LINE];
		char w0[MAX_ONE_LINE];
		char w1[MAX_ONE_LINE];
		char wn[MAX_ONE_LINE];
		char b0[MAX_ONE_LINE];
		char b1[MAX_ONE_LINE];
		char bn[MAX_ONE_LINE];
		char result[MAX_ONE_LINE];
		char moves[MAX_ONE_LINE];
		char round[MAX_ONE_LINE];
		char byo[MAX_ONE_LINE];
		sscanf(one_line,"%s %s %s %s %s %s %s %s %s %s %s %s %s",
			id,date,hm,w0,w1,wn,b0,b1,bn,result,moves,round,byo);
//		printf("%8s %s %s %s %s %s %s %s %s %s %s %s %s\n",
//			id,date,hm,w0,w1,wn,b0,b1,bn,km,result,round,byo);
//		printf("%8s %s %s %10s %s %10s %s %-9s %3s %s %3s\n",
//			id,date,hm,w1,wn,b1,bn,km,result,round,byo);

		char one_sgf[MAX_ONE_SGF];
		fgets_sgf( one_sgf, MAX_ONE_SGF );
		int len = strlen(one_sgf);
		if ( len >= MAX_ONE_SGF-1 ) { printf("too big, %s\n",one_sgf); exit(0); }
		char id_sgf[MAX_ONE_SGF];
		char sgf[MAX_ONE_SGF];
		sscanf(one_sgf,"%s %s",id_sgf,sgf);
		if ( strcmp(id,id_sgf)!=0 ) { printf("id err, %s %s,lines=%d\n",id,id_sgf,lines); exit(0); }
//		printf("%s",sgf);

		lines++;
//		if ( lines > 100 ) break;
		char filename[256];
		sprintf(filename,"%04d/%04d%06d.sgf",year,year,lines);
		FILE *fp_out = fopen(filename,"w");
		if ( fp_out==NULL ) { printf("fp_out err=%s\n",filename); exit(0); }
		fprintf(fp_out,"(;GM[1]\nKM[6.5]\nRU[Japanese]\nGN[%s]\nPW[%s]\nPB[%s]\nRE[%s]\n",id,w1,b1,result);
		date[5]='-';
		date[8]='-';
		fprintf(fp_out,"DT[%s]\nEV[%s,%s,%s,%s,%s]\n",&date[1],wn,bn,moves,round,byo);
		fprintf(fp_out,"%s)",sgf);
		fclose(fp_out);
	}
	printf("year=%d,lines=%d\n",year,lines);

	return 0;
}
