#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
//--------------API area---------------------------
class PrintStream{
	map<string,string>Translate;
	public:
		PrintStream operator<<(string s){
			if(Translate[s].empty())cout<<s;
			else cout<<Translate[s];
			return *this;
		}
		PrintStream operator<<(char ch){
			if(ch=='\n')cout<<endl;
			else cout<<ch;
			return *this;
		}
		PrintStream operator<<(int ch){
			cout<<ch;
			return *this;
		}
		void operator>>(const char* Path){
			ifstream Tsl(Path);
			int p;
			Tsl>>p;
			if(p!=91)return;
			while(1){
				string a,b;
				Tsl>>a;
				//cout<<a<<'\n';
				if(a=="EOF")break;
				Tsl>>b;
				Translate[a]=b;
			}
		}
		void Read(const char* Path){
			ifstream Tsl(Path);
			while(1){
				string a,b;
				Tsl>>a;
				//cout<<a<<'\n';
				if(a=="EOF")break;
				Tsl>>b;
				Translate[a]=b;
			}
		}
};
PrintStream print;
bool StartF=0;
void PutAllStringsln(vector<string> strs){
	for(auto p:strs)print<<p<<'\n';
	cout<<flush;
}
int ChooseMenu(vector<string> strs,vector<string> prev,vector<string> ends,int maxpos,string nc,string cho,char Conrrect,char SeceltUP,char SeceltDOWN,char QUIT){
	int pos=0;
	system("cls");
	PutAllStringsln(prev);
	for(int i=0;i<maxpos;i++){
			if(i!=pos)print<<nc;
			else print<<cho;
			print<<strs[i]<<'\n';
	}
	PutAllStringsln(ends);
	while(1){
		char ch=getch();
		system("cls");
		if(ch==SeceltDOWN){
			pos=(pos+1)%maxpos;
		}
		if(ch==SeceltUP){
			pos=(pos-1+maxpos)%maxpos;
		}
		if(ch==Conrrect)break;
		if(ch==QUIT)return -1;
		PutAllStringsln(prev);
		for(int i=0;i<maxpos;i++){
			if(i!=pos)print<<nc;
			else print<<cho;
			print<<strs[i]<<'\n';
		}
		cout<<flush;
		PutAllStringsln(ends);
	}
	system("cls");
	return pos;
}
void Setpos(int x,int y){
	COORD pos;
	pos.X=y,pos.Y=x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
} 
void color(int x){
	SetConsoleTextAttribute(GetStdHandle(4294967285u),x);
}
void langread() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string searchPath ="lang\\*";
    hFind = FindFirstFile(searchPath.c_str(), &findFileData);
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        	//cout<<strcat("lang\\",findFileData.cFileName)<<endl; 
        	string t="lang\\";
        	string s=t+findFileData.cFileName;
        	print>>s.c_str();
        }
    	//cout<<91<<endl;
    } while (FindNextFile(hFind, &findFileData) != 0);
    FindClose(hFind);
    //Sleep(1919);
}

//---------------main area-------------------------
class liquid{
	public:
		string ID;
		int price;
		liquid(string id,int p){
			ID=id,price=p;
		}
		liquid()=default;
};

class liquid_tank{
	int Max_V;
	liquid liquid_type;
	public:
	int price;
	string ID;
	liquid_tank(int v,liquid tpe){
		this->Max_V=v;
		this->liquid_type=tpe;
		ID="Tank";
	}
	liquid_tank(int v,liquid tpe,string id,int p){
		this->Max_V=v;
		this->liquid_type=tpe;
		ID=id;
		price=p;
	}
	liquid type(){
		return liquid_type;
	}
	int value(){
		return Max_V;
	}
	liquid_tank()=default;
};
class collector{
	int P10s,EU;
	liquid Type;
	bool nempty=0;
	public:
	int OP(){
		return P10s;
	}
	liquid type(){
		return Type;
	}
	int getEU(){
		return this->EU;
	}
	int price;
	string ID;
	collector(int k,liquid tpe){
		P10s=k;
		Type=tpe;
		ID="Milk_collector";
		nempty=1;
	}
	collector(int k,liquid tpe,string id,int p){
		P10s=k;
		ID=id;
		Type=tpe;
		price=p;
		nempty=1;
	}
	collector(){
		ID="Empty";
		nempty=0;
	}
	bool empty(){
		return this->nempty==0;
	}
};
class stuff{
	public:
	string ID;
	int price;
	stuff(string s,int p){
		price=p,ID=s;
	}
	stuff()=default;
};
class generator{
	int maxeu,fuel,mineu,fuelpereu,fuelmax;
	map<string,int>fueltype;
	public:
		int price;string ID;
		int EU(){
			int fueldmx=(maxeu-mineu)*fuelpereu;
			if(fuel<fuelpereu)return mineu;
			if(fuel>=fueldmx){
				fuel-=fueldmx;
				return maxeu;
			}
			int euf=fuel/fuelpereu*fuelpereu;
			fuel-=euf;
			return euf/fuelpereu;
		}
		int pushfuel(stuff s){//return not failed things
			string ID=s.ID;
			int w=fueltype[ID];
			if(!w)return 0;
			int de=(fuelmax-fuel)/w;
			fuel+=de*w;
			return de;
		}
		void plusfueltype(string s,int w){
			fueltype[s]=w;
		}
		generator(){
			ID="Empty";
		}
		generator(int mxe,int mne,int fpe,int fmx,int p,string s){
			maxeu=mxe,mne=mineu,fuelpereu=fpe,fuelmax=fmx,price=p,ID=s;
		}
};
class crafting{
	public:
	map<string,int>ms,as;
	map<string,int>ml,al;
	string ID,crafting_type;
	crafting()=default;
	crafting(string ct,string s){
		ID=s;
		crafting_type=ct;
	}
};
class machine{
	int euper,mxparallel;
	vector<string>usingtype;
	public:
	int price;string ID;
	bool check(crafting cf){
		for(string s:usingtype)
			if(cf.crafting_type==s)return true;
		return false;
	}
	int craft(){
		return euper;
	}
};
class battery{
	int eu_max;
	public:
	int price;string ID;
	battery(){
		ID="Empty";
	}
	battery(int eu,string id,int p){
		eu_max=eu,price=p,ID=id;
	}
	int EU(){
		return eu_max;
	}
};
class shop{
	public:
	vector<collector>sellcol;
	vector<liquid_tank>selltank;
	vector<stuff>sellstuff;
	string ID;
	vector<string> stuffs(){
		vector<string> res;
		char buf[1145];
		for(auto i:sellstuff){
			res.push_back(i.ID+'('+itoa(i.price,buf,10)+"$)");
		}
		return res;
	}
	vector<string> collectors(){
		vector<string> res;
		char buf[1145];
		for(auto i:sellcol){
			res.push_back(i.ID+'('+itoa(i.price,buf,10)+"$)");
		}
		return res;
	}
	vector<string> tanks(){
		vector<string> res;
		char buf[1145];
		for(auto i:selltank){
			res.push_back(i.ID+'('+itoa(i.price,buf,10)+"$)");
		}
		return res;
	}
	vector<string>types(){
		return {"Collector","Tank","Stuff"};
	}
};
int ChooseNumber(string guide,string e,char up,char down,char cor){
	print<<guide<<'\n';
	print<<0<<e<<'\n';
	int result=0;
	while(1){
		char ch=getch();
		if(ch==up-32)result+=10;
		if(ch==down-32)result-=10;
		if(ch==up)result++;
		if(ch==down)result--;
		if(result<0)result=0;
		system("cls");
		if(ch==cor)return result;
		print<<guide<<'\n';
		print<<result<<e<<'\n';
	}
	return 0;
}
map<string,liquid>LqdTypes;
map<string,liquid_tank>LqdTnkTypes;
map<string,collector>CltorTypes;
map<string,stuff>StuffTypes;
map<string,crafting>CraftingList;
void s2mf(string s){print<<StuffTypes[s].price<<"G/per"<<'\n';}
void l2mf(string s){print<<LqdTypes[s].price<<"G/mB"<<'\n';}
void t2mf(string s){
	print<<LqdTnkTypes[s].price<<"G/per"<<'\n';
	print<<"MaxV:"<<LqdTnkTypes[s].value()<<'\n';
}
void c2mf(string s){
	print<<CltorTypes[s].price<<"G/per"<<'\n';
	print<<"LiquidType:"<<CltorTypes[s].type().ID<<'\n';
	print<<"Speed:"<<CltorTypes[s].OP()<<"mB/10s"<<'\n';
}
void cf2f(string s){
	print<<"MaterialStuff"<<'\n';
	for(auto a:CraftingList[s].ms)print<<a.second<<"x"<<a.first;
	print<<'\n'<<"MaterialLiquid"<<'\n';
	for(auto a:CraftingList[s].ml)print<<a.second<<a.first<<"mB";
	print<<'\n';
}
function<void(string)>s2m=s2mf,l2m=l2mf,t2m=t2mf,c2m=c2mf,cf2=cf2f;
void CreateObjects(){
	LqdTypes["Milk"]={"Milk",10};
	LqdTypes["Cocomilk"]={"Cocomilk",30};
	LqdTnkTypes["MilkTankLv1"]={8000,LqdTypes["Milk"],"MilkTankLv1",100};
	LqdTnkTypes["MilkTankLv2"]={16000,LqdTypes["Milk"],"MilkTankLv2",200};
	CltorTypes["CowLv1"]={20,LqdTypes["Milk"],"CowLv1",300};
	CltorTypes["CowLv2"]={50,LqdTypes["Milk"],"CowLv2",1000};
	CltorTypes["CowLv3"]={100,LqdTypes["Milk"],"CowLv3",3000};
	StuffTypes["Chocolate"]={"Chocolate",10};
	CraftingList["Cocomilk"]={"Common","Cocomilk"};
	CraftingList["Cocomilk"].al["Cocomilk"]=50;CraftingList["Cocomilk"].ml["Milk"]=40;CraftingList["Cocomilk"].ms["Chocolate"]=1;
	
}
void CreateModObjects(string name){
	string path=name;
	int n,t,t1,t2;string s,s1,s2;
	ifstream fin(path);
	fin>>n;//Liquid 
	while(n--){
		int price;
		fin>>price>>s;
		LqdTypes[s]={s,price};
	}
	fin>>n;//Tank
	while(n--){
		int v,price;
		fin>>v>>s1>>s>>price;
		LqdTnkTypes[s]={v,LqdTypes[s1],s,price};
	}
	fin>>n;//Col
	while(n--){
		int v,price;
		fin>>v>>s1>>s>>price;
		CltorTypes[s]={v,LqdTypes[s1],s,price};
	}
	fin>>n;//Stuffs
	while(n--){
		int price;
		fin>>price>>s;
		StuffTypes[s]={s,price};
	}
	fin>>n;//Crafting
	while(n--){
		fin>>s>>s1;//Type&ID
		CraftingList[s1]={s,s1};
		fin>>t;//ms
		while(t--)fin>>s2>>t1,CraftingList[s1].ms[s2]=t1;
		fin>>t;//ml
		while(t--)fin>>s2>>t1,CraftingList[s1].ml[s2]=t1;
		fin>>t;//as
		while(t--)fin>>s2>>t1,CraftingList[s1].as[s2]=t1;
		fin>>t;//al
		while(t--)fin>>s2>>t1,CraftingList[s1].al[s2]=t1;
		//ID&pcs
	}
}
void modread() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string searchPath ="mods\\*";
    hFind = FindFirstFile(searchPath.c_str(), &findFileData);
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        	string t="mods\\";
        	string s=t+findFileData.cFileName;
        	cout<<s<<endl; 
        	CreateModObjects(s);
        }
    	//cout<<91<<endl;
    } while (FindNextFile(hFind, &findFileData) != 0);
    FindClose(hFind);
    //Sleep(1919);
}//Reoperation
int ChooseMenu(vector<string> strs,vector<string> prev,vector<string> ends,int maxpos,string nc,string cho,
char Conrrect,char SeceltUP,char SeceltDOWN,char QUIT,function<void(string)> func){
	int pos=0;
	system("cls");
	PutAllStringsln(prev);
	for(int i=0;i<maxpos;i++){
			if(i!=pos)print<<nc;
			else print<<cho;
			print<<strs[i]<<'\n';
	}
	PutAllStringsln(ends);
	while(1){
		char ch=getch();
		system("cls");
		if(ch==SeceltDOWN){
			pos=(pos+1)%maxpos;
		}
		if(ch==SeceltUP){
			pos=(pos-1+maxpos)%maxpos;
		}
		if(ch==Conrrect)break;
		if(ch==QUIT)return -1;
		PutAllStringsln(prev);
		for(int i=0;i<maxpos;i++){
			if(i!=pos)print<<nc;
			else print<<cho;
			print<<strs[i]<<'\n';
		}
		cout<<flush;
		PutAllStringsln(ends);
		func(strs[pos]);
		cout<<flush;
	}
	system("cls");
	return pos;
}
class Player{
	int Money,Tank_Max,Cow_Count,Cow_price,Collector_Max;
	string Name;
	map<string,int>LqdMax_V;
	map<string,int>Lqd_V;
	map<string,int>Stuff_Count;
	vector<collector>Collectors;
	bool ColState[1145]={0};
	vector<liquid_tank>Tanks;
	vector<collector>Equip;
	map<string,bool>UsefulCrafting;
	public:
		void money_plus(int m){
			Money+=m;
		}
		void BuyTank(liquid_tank Tk){
			if(Tk.price>Money){
				print<<"Not_enough_money";
				return;
			}
			if(Tanks.size()==Tank_Max){
				print<<"Tank_overflow";
				return;
			}
			LqdMax_V[Tk.type().ID]+=Tk.value();
			this->Money-=Tk.price;
			Tanks.push_back(Tk);
		}		
		void BuyCollector(collector Cl){
			if(Cl.price>Money){
				print<<"Not_enough_money";
				Sleep(250);
				return;
			}
			if(Collectors.size()==Collector_Max){
				print<<"Collector_overflow";
				return;
			}
			this->Money-=Cl.price;
			Collectors.push_back(Cl);
		}
		void BuyCow(){
			if(Cow_price>Money)Sleep(500),print<<"Not_enough_money";
			else Cow_Count++,Equip.push_back(collector()),Cow_price*=1.2;
		}
		void BuyStuff(int i,string stf){
			stuff s=StuffTypes[stf];
			if(i*s.price>this->Money){
				print<<"Not_enough_money";Sleep(200);
				return;
			}
			this->Money-=i*s.price;
			this->Stuff_Count[stf]+=i;
		}
		void ExpMax(int i){
			if(Money<=i*1000)return;
			Tank_Max+=i,Collector_Max+=i;
			Money-=i*1000;
		}
		Player(){
			if(!StartF)return;
			this->Collector_Max=10;
			this->Cow_Count=1;
			this->Money=1500;
			this->Tank_Max=5;
			this->Cow_price=300;
			this->BuyCollector(CltorTypes["CowLv1"]);
			this->BuyTank(LqdTnkTypes["MilkTankLv1"]);
			this->UsefulCrafting["Common"]=1;
			print<<"scan_name"<<'\n';
			bool f=0;
			do {
				if(f)print<<"scan_again"<<'\n';
				cin>>this->Name;
				f=1;
			}while(MessageBox(NULL,"Did you think?","SYSTEM",MB_YESNO)!=6);
			int cnt=1;
			while(cnt--){
				Equip.push_back(collector());
			}
		}
		void EquipC(){
			vector<string> E,C;
			vector<string>EP;
	
			for(collector c:Equip){
				//cout<<1<<flush;
				E.push_back(c.ID);
			}
			int i=0;
			int MP[1145]={0};
			for(collector c:Collectors){
				if(c.empty()||ColState[i]){
					i++;
					continue;
				}
				MP[C.size()]=i;
				i++;
				C.push_back(c.ID);
				//cout<<c.ID<<endl;
			}
			if(C.empty()){
				print<<"NOCOLLECTOR";
				return;
			}
			int Ei=ChooseMenu(E,{"Choose_Equip"},EP,E.size(),"----","--->",'e','w','s','q');
			if(Ei==-1)return;
			int Ci=ChooseMenu(C,{"Choose_Collector"},EP,C.size(),"----","--->",'e','w','s','q');
			if(Ci==-1)return;
			//cout<<Equip[Ei].empty()<<" "<<Collectors[MP[Ci]].ID<<endl;
			if(!Equip[Ei].empty())
				this->ColState[Ei]=0;
			this->ColState[MP[Ci]]=1;
			Equip[Ei]=Collectors[MP[Ci]];
		}
		void Statuslist(){
			print<<Name<<"'s" <<"StatusList"<<'\n';
			print<<"EquipCollector"<<'\n';
			for(collector c:Equip){
				//if(c.empty())continue;
				print<<c.ID<<' ';
			}
			print<<'\n'<<"AllCollector"<<'\n';
			int i=0;
			for(collector c:Collectors){
				if(c.empty()){
					i++;
					continue;
				}
				print<<c.ID;
				if(ColState[i])print<<"(Equiped)";
				print<<' ';
				i++;
			}
			print<<'\n'<<"AllLiquid"<<'\n';
			for(auto t:Lqd_V){
				print<<t.first<<' '<<t.second<<"mB"<<'\n';
			}
			print<<"AllLiquidMax"<<'\n';
			for(auto t:LqdMax_V){
				print<<t.first<<' '<<t.second<<"mB"<<'\n';
			}
			print<<"Tanks"<<'\n';
			for(auto t:Tanks){
				print<<t.type().ID<<" "<<t.value()<<"mB"<<'\n';
			}
			print<<"AllStuff"<<'\n';
			for(auto t:Stuff_Count){
				print<<t.first<<" x"<<t.second<<'\n';
			}
			print<<"Coin:"<<Money<<"CowCount:"<<Cow_Count<<'\n';
		}
		map<string,int> Cresult(){
			map<string,int>Res;
			for(auto c:Equip){
				if(!c.type().ID.empty())
					Res[c.type().ID]+=c.OP();
			}
			return Res;
		}
		void Addresult(){
			map<string,int>R=this->Cresult();
			for(auto a:R){
				this->Lqd_V[a.first]=min(this->LqdMax_V[a.first],this->Lqd_V[a.first]+a.second);
			}
		}
		void SellLiquid(string s,int mB){
			int t=min(this->Lqd_V[s],mB);
			Lqd_V[s]-=t;
			this->money_plus(t*LqdTypes[s].price);
		}
		void Save(){
			string File="saves\\save_"+Name+".txt";
			ofstream out(File);
			out<<Equip.size()<<'\n';
			for(collector c:Equip){
				//if(c.empty())continue;
				out<<c.ID<<' ';
			}
			out<<'\n'<<Collectors.size()<<'\n';
			int i=0;
			for(collector c:Collectors){
				out<<c.ID<<' '<<ColState[i]<<'\n';
				i++;
			}
			out<<Lqd_V.size()<<'\n';
			for(auto t:Lqd_V){
				if(t.first.empty())continue;
				out<<t.first<<' '<<t.second<<'\n';
			}
			out<<Stuff_Count.size()<<'\n';
			for(auto t:Stuff_Count){
				if(t.first.empty())continue;
				out<<t.first<<' '<<t.second<<'\n';
			}
			out<<LqdMax_V.size()<<'\n';
			for(auto t:LqdMax_V){
				if(t.first.empty())continue;
				out<<t.first<<' '<<t.second<<'\n';
			}
			out<<Tanks.size()<<'\n';
			for(auto t:Tanks){
				if(t.type().ID.empty())continue;
				out<<t.ID<<" "<<t.value()<<'\n';
			}
			out<<this->UsefulCrafting.size()<<'\n';
			for(auto t:UsefulCrafting){
				if(t.second)out<<t.first<<'\n';
			}
			out<<Money<<"\n"<<Cow_Count<<'\n'<<Tank_Max<<'\n'<<Collector_Max<<'\n'<<Cow_price<<'\n';
		}
		Player(string name){
			string File="saves\\save_"+name+".txt";
			Name=name;
			ifstream fin(File);
			int n,t,i=0;
			string s;
			fin>>n;
			while(n--){
				fin>>s;
				Equip.push_back(CltorTypes[s]);
			}
			fin>>n;
			while(n--){
				fin>>s>>t;
				Collectors.push_back(CltorTypes[s]);
				ColState[i]=t;
				i++;
			}
			i=0;
			fin>>n;
			while(n--){
				fin>>s>>t;
				Lqd_V[s]=t;
			}
			fin>>n;
			while(n--){
				fin>>s>>t;
				Stuff_Count[s]=t;
			}
			fin>>n;
			int t1;
			while(n--){
				fin>>s>>t;
				LqdMax_V[s]=t;
			}
			fin>>n;
			while(n--){
				fin>>s>>t1;
				Tanks.push_back(LqdTnkTypes[s]);
			}
			fin>>n;
			while(n--){
				fin>>s;
				this->UsefulCrafting[s]=1;
			}
			fin>>Money>>Cow_Count>>Tank_Max>>Collector_Max>>Cow_price;
		}
		bool operation(){
			vector<string>Opts={"Status","Shop","Sell","Equip","Save","Craft"},Emp,title={"Operations"}
			,Cols,Tnks,Item={"Collector","Tank","Stuff","Cow","Express"},liquids,stuffs;
			for(auto i:CltorTypes){
				if(i.second.empty())continue;
				Cols.push_back(i.first);
			}for(auto i:LqdTnkTypes){
				Tnks.push_back(i.first);
			}
			for(auto i:Lqd_V){
				if(i.second==0)Lqd_V.erase(i.first);
				liquids.push_back(i.first);
			}
			for(auto i:StuffTypes){
				if(Stuff_Count[i.first]==0)Stuff_Count.erase(i.first);
				stuffs.push_back(i.first);
			}
			int Optid=ChooseMenu(Opts,title,Emp,Opts.size(),"----","--->",'e','w','s','q');
			if(Optid==-1)return 0;
			switch(Optid){
				case 0:{
					this->Statuslist();
					system("pause");
					Sleep(150);
					break;
				}
				case 1:{
					int Itemid=ChooseMenu(Item,Emp,Emp,Item.size(),"----","--->",'e','w','s','q');
					if(Itemid==-1)break;
					int Id;
					if(Itemid==0){
						Id=ChooseMenu(Cols,Emp,Emp,Cols.size(),"----","--->",'e','w','s','q',c2m);
						if(Id==-1)break;
						this->BuyCollector(CltorTypes[Cols[Id]]);
					}
					else if(Itemid==1){
						Id=ChooseMenu(Tnks,Emp,Emp,Tnks.size(),"----","--->",'e','w','s','q',t2m);
						if(Id==-1)break;
						this->BuyTank(LqdTnkTypes[Tnks[Id]]);
					}
					else if(Itemid==2){
						Id=ChooseMenu(stuffs,Emp,Emp,stuffs.size(),"----","--->",'e','w','s','q',s2m);
						if(Id==-1)break;
						int t=ChooseNumber("Stuff_Count","pcs",'w','s','e');
						this->BuyStuff(t,stuffs[Id]);
					}
					else if(Itemid==3)this->BuyCow();
					else this->ExpMax(1);
					break;
				}
				case 2:{
					int t,Id;
					if(liquids.empty()){
						print<<"Failed"<<'\n';
						Sleep(200);
						break;
					}
					Id=ChooseMenu(liquids,Emp,Emp,liquids.size(),"----","--->",'e','w','s','q',l2m);
					if(Id==-1)break;
					t=ChooseNumber("Liquid_Sell","mB",'w','s','e');
					this->SellLiquid(liquids[Id],t);
					break;
				}
				case 3:{
					EquipC();
					break;
				}
				case 4:{
					Save();
					print<<"User"<<' '<<Name<<"\'s"<<"Data" <<' '
					<<"has_been_saved!"<<'\n';
					system("pause");
					Sleep(150);
					break;
				}
				case 5:{
					string itoc[1145];int ind=-1;
					vector<string>craft;
					for(auto i:CraftingList){
						craft.push_back(i.first);
						itoc[++ind]=i.first;
					}
					int Id=ChooseMenu(craft,Emp,Emp,craft.size(),"----","---->",'e','w','s','q',cf2);
					if(Id==-1)break;
					string Cid=itoc[Id];
					crafting cf=CraftingList[Cid];
					if(this->UsefulCrafting[cf.crafting_type]==0){
						print<<"craft_failed";
						Sleep(501);
						break;
					}
					int t=ChooseNumber("Craft","times",'w','s','e');
					while(t--){
						int f=1;
						for(auto i:cf.ms){
							if(this->Stuff_Count[i.first]<i.second)f=0;
						}
						for(auto i:cf.ml){
							if(this->Lqd_V[i.first]<i.second)f=0;
						}
						if(!f){
							print<<"craft_failed";
							Sleep(590);
							break;
						}
						for(auto i:cf.ms){
							this->Stuff_Count[i.first]-=i.second;
						}
						for(auto i:cf.ml){
							this->Lqd_V[i.first]-=i.second;
						}
						for(auto i:cf.as){
							this->Stuff_Count[i.first]+=i.second;
						}
						for(auto i:cf.al){
							this->Lqd_V[i.first]+=i.second;
						}
					}
					break;
				}
			}
			return true;
		}
};
Player O;
void milkopt(){
	while(1){
		Sleep(10000);
		O.Addresult();
	}
}
void configinit(){
	system("mkdir saves");
	system("mkdir mods");
	system("mkdir lang");
}
void Startgame(){
	color(0xf0+0xa);
	print<<"Created by Yyz140116"<<'\n';
	print<<"Press Any Keys to Start Game."<<'\n';
  print<<"Version:1.0"<<'\n';	
  system("pause");
	system("cls");
}
int main(){
	Startgame();
	ReStart:
	configinit();
	langread();
	CreateObjects();
	modread();
	system("cls");
	//print>>"zh_CN.txt";
	string s;
	print<<"输入昵称(输入Rebirth重新开始,Q&A打开Q&A页面)\n";
	cin>>s;
	StartF=1;
	if(s=="Rebirth"){
		O=Player();
	}
	else if(s=="Q&A"){
		system("start https://www.luogu.me/paste/auhb0cip");goto ReStart;
	}
	else O=Player(s);
	std::thread t1(milkopt);
	t1.detach();
	while(O.operation());
}


