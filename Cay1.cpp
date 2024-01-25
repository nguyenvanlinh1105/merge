#include <stdio.h>
struct NUT 
		{
			int dlieu;
			NUT *L, *R;
		};
NUT *BSUNG(NUT *Cay, NUT *ptu)
{
	NUT *tg, *tr;
	if (Cay ==NULL)
		Cay = ptu;
	else
	{
		tg = Cay;
		while (tg!=NULL)
		{
			tr = tg;
			if (tg->dlieu > ptu->dlieu)
				tg = tg->L;
			else
				tg = tg->R;	
		}
		if (tr->dlieu > ptu->dlieu)
			tr->L = ptu;
		else
			tr->R = ptu;	
	}
	return Cay;		
}	
void INCAY(NUT *Cay)
{
	if (Cay!=NULL)
	{
		
		INCAY(Cay->L);	
		printf("%d ", Cay->dlieu);	
		INCAY(Cay->R);
	}
}
int TKIEM_1(NUT *Cay, int x)
{
	NUT *tg;
	tg = Cay;
	while (tg!=NULL && tg->dlieu!=x)
		if (x < tg->dlieu )
			tg = tg->L;
		else
			tg = tg->R;
	if (tg!=NULL)
		return 1;
	else
		return 0;				
}	
NUT *TKIEM_2(NUT *Cay, int x)
{
	NUT *tg;
	tg = Cay;
	while (tg!=NULL && tg->dlieu!=x)
		if (x < tg->dlieu )
			tg = tg->L;
		else
			tg = tg->R;
	if (tg!=NULL)
		return tg;
	else
		return NULL;				
}
NUT *XOA_GOC(NUT *Cay)
{	
	NUT *tg, *CayL, *CayR;
	if (Cay->L == NULL && Cay->R == NULL)
		return NULL;
	tg = Cay;
	if (Cay->L != NULL && Cay->R == NULL)
	{		
		Cay = Cay->L;
		tg->L = NULL;
	}
	if (Cay->L == NULL && Cay->R != NULL)
	{
		Cay = Cay->R;
		tg->R = NULL;
	}	
	if (Cay->L != NULL && Cay->R != NULL)
	{
		CayL = Cay->L;	
		CayR = Cay->R;
		tg->L =NULL;
		tg->R = NULL;
		Cay = CayR;	
		tg = CayR;
		while (tg->L !=NULL)
			tg = tg->L;
		tg->L = CayL;	
	}
	return Cay;
}
NUT *XOA_LA(NUT *Cay, NUT *nut)
{
	NUT *tg;
	tg =Cay;
	while (tg->L !=nut && tg->R !=nut)
  		if (nut->dlieu < tg->dlieu)
     		tg=tg->L;
  		else 
			tg = tg->R;
	if (tg->L==nut)
		tg->L=NULL;
	else
		tg->R=NULL;
	return Cay;	
}
NUT *XOA_TG(NUT *Cay, NUT *nut)
{
	NUT *tg, *CayL, *CayR;
	if (nut->R == NULL)//Cay lech trai
	{		
		tg =Cay;
		while (tg->L !=nut && tg->R !=nut)
  			if (nut->dlieu < tg->dlieu)
     			tg=tg->L;
  			else 
				tg = tg->R;
		if (tg->L==nut)
		{
			tg->L = nut->L;		
			nut->L = NULL;
		}	
		else
		{
			tg->R = nut->L;		
			nut->L = NULL;
		}		
	}
	else
		if (nut->L == NULL)//Cay lech phai
		{		
			tg =Cay;
			while (tg->L !=nut && tg->R !=nut)
  				if (nut->dlieu < tg->dlieu)
     				tg=tg->L;
  				else 
					tg = tg->R;
			if (tg->L==nut)
			{
				tg->L = nut->R;		
				nut->R = NULL;
			}	
			else
			{
				tg->R = nut->R;		
				nut->R = NULL;
			}	
						
		}
		else
		{
			tg = Cay;
			while (tg->L !=nut && tg->R !=nut)
  				if (nut->dlieu < tg->dlieu)
     				tg=tg->L;
  				else 
					tg = tg->R;
			CayL= nut->L;
			CayR = nut->R;
			nut->L = NULL;
			nut->R = NULL;
			if (tg->R == nut)
			{
				tg->R = CayR;
				Cay = BSUNG(Cay, CayL);
			}
			else
			{
				tg->L = CayR;
				Cay = BSUNG(Cay, CayL);
			}
			
		}
	return Cay;
}
NUT *XOA(NUT *Cay, int x)
{
	NUT *tk;  
	while (TKIEM_2(Cay, x)!=NULL)
	{
		tk = TKIEM_2(Cay, x);
		if (tk==Cay )		//Xoa Goc
			Cay = XOA_GOC(Cay);
		else
			if (tk->L ==NULL &&tk->R ==NULL )
				Cay = XOA_LA(Cay, tk);
			else
			 	Cay = XOA_TG(Cay, tk);
				
	}
	return Cay;
}
main()
{
	NUT *Tree, *p;
	int i, n, so ;
	printf("Nhap bao nhieu so: ");
	scanf("%d", &n);
	Tree=NULL;
	for (i=1;i<=n; i++)
	{
		p= new NUT;		
		printf("Nhap so thu %d: ", i);
		scanf("%d", &p->dlieu);
		p->L=NULL;
		p->R=NULL;
		Tree = BSUNG(Tree, p);
	}
	INCAY(Tree);
	printf("\nNhap so can xoa: ");
	scanf("%d", &so);
	Tree= XOA(Tree, so);	
	INCAY(Tree);	
}
