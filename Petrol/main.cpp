#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_cfg_size 10000

typedef struct lista {
	int			id;
	struct lista	*next;
} lista;


int nbb;

int src;

lista *bb_succ[max_cfg_size]; 		// listele de succesori
lista *bb_pred[max_cfg_size]; 		// listele de predecesori


int im_dom[max_cfg_size];		// immediate dominator
int dfs_no[max_cfg_size];
int dom_visited[max_cfg_size];
int changed;


int dep_nr[max_cfg_size];
int dep_min[max_cfg_size];
int dep_max[max_cfg_size];

int   add_to_list (lista **l, int pid)
{
	lista *tmp;
	tmp = (lista *) malloc( sizeof ( lista ) );
	tmp->id = pid;
	tmp->next = *l;
	*l = tmp;
	return 0;
}


void add_edge(int src, int dst)
{
	add_to_list(&bb_succ[src], dst);
	add_to_list(&bb_pred[dst], src);
}



void read_input()
{
	FILE *f;
	int i,j,k,m;

	f = fopen("petrol.in", "r");
	fscanf(f, "%d %d %d", &nbb, &m, &src);

	for (i=0; i<=nbb; i++)
	{
		bb_succ[i] = NULL;
		bb_pred[i] = NULL;
	}

	for (k=0; k<m; k++)
	{
		fscanf(f, "%d %d", &i, &j);
		add_edge(i,j);
	}
	fclose(f);
}

int  intersect(int i1, int i2)
{
	while (i1!=i2)
	{
		while ( dfs_no[i1] < dfs_no[i2] ) i1 = im_dom[i1];
		while ( dfs_no[i2] < dfs_no[i1] ) i2 = im_dom[i2];
	}
	return i1;
}


int counter = 1;

void dfs(int x)
{
	lista *f;
	dfs_no[x] = 1;
	for (f=bb_succ[x]; f!=NULL; f=f->next)
		if (dfs_no[f->id]==0)
			dfs(f->id);
	dfs_no[x] = counter++;
}


void dom_dfs(int x, int k)
{
	int p;
	lista *f;

	p = -1;

	if (x!=src)
	for (f=bb_pred[x]; f!=NULL; f=f->next)
		if (im_dom[f->id]!=-1 && dfs_no[f->id]!=0)
		{
			if (p==-1)  p = f->id;
				else 	p = intersect(p, f->id);
		}


	if (im_dom[x]!=p && p!=-1)
	{
		im_dom[x] = p;
		changed = 1;
	}

	dom_visited[x] = k;
	for (f=bb_succ[x]; f!=NULL; f=f->next)
		if (dom_visited[f->id]!=k)
			dom_dfs(f->id, k);
}


void dominators()
{
	int i,k;

	for (i=0; i<=nbb; i++)
	{
		im_dom[i] = -1;
		dom_visited[i] = 0;
		dfs_no[i] = 0;

		dep_nr[i] = -1;
		dep_max[i] = -1;
		dep_min[i] = -1;
	}
	dfs(src);

	im_dom[src] = 0;
	changed = 1;
	k = 1;

	while (changed)
	{
		changed = 0;
		dom_dfs(src, k);
		k = 1 - k;
	}
}

void calc_doms(int x)
{
	int t;
	if (dep_nr[x]!=-1) return; // a fost calculat

	t = im_dom[x];
	if (t==0 || t==-1)
	{
		dep_nr[x]=0;
		dep_min[x] = x;
		dep_max[x] = x;
		return;
	}

	if (dep_nr[t]==-1) calc_doms(t);

	dep_nr[x] = dep_nr[t]+1;
	dep_min[x] = dep_min[t];
	if (t<dep_min[x]) dep_min[x] = t;
	dep_max[x] = dep_max[t];
	if (t>dep_max[x]) dep_max[x] = t;
}

void print_doms()
{
	int i;
	FILE *f = fopen("petrol.out", "w");

	for (i=1; i<=nbb; i++)
	{
		calc_doms(i);
		if (dep_nr[i]!=0)
			fprintf(f,"%d", dep_nr[i]);
		else
			fprintf(f,"0");
		fprintf(f,"\n");
	}
	fclose(f);
}

int main()
{
	read_input();
	dominators();
	print_doms();

	return 0;
}
