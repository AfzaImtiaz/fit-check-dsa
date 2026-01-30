#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;
struct OutfitBasic{
    int id;
    string type;
    string color;
    string season;
};
OutfitBasic outfits[5];
int n=5;
void storeOutfits(){
    outfits[0]={3, "Jacket", "Brown", "Winter"};
    outfits[1]={1, "T-Shirt", "White", "Summer"};
    outfits[2]={5, "Raincoat", "Blue", "Rainy"};
    outfits[3]={2, "T-Shirt", "Black", "Summer"};
    outfits[4]={4, "Hoodie", "Grey", "Winter"};
}

void SortSeason() 
{
    for(int i=0; i<n-1; i++) 
	{
        for(int j=0; j<n-i-1; j++) 
		{
            if(outfits[j].season>outfits[j+1].season) 
			{
                OutfitBasic temp=outfits[j];
                outfits[j]=outfits[j+1];
                outfits[j+1]=temp;
            }
        }
    }
}
void SearchSeasonOutfits(string key) 
{
    bool found = false;
    for(int i = 0; i < n; i++) 
    {
        string seasonLower = "";	
        for(int j = 0; j < outfits[i].season.length(); j++)
        {
            seasonLower += tolower(outfits[i].season[j]);
        }
        string keyLower = "";
        for(int j = 0; j < key.length(); j++)
        {
            keyLower += tolower(key[j]);
        }
        if(seasonLower == keyLower) 
        {
            cout << "Outfit ID: " << outfits[i].id << endl;
            cout << "Type: " << outfits[i].type << endl;
            cout << "Color: " << outfits[i].color << endl;
            cout << "Season: " << outfits[i].season << endl;
            found = true; }
    }
    if(!found) 
    {
        cout << "No outfit found for that season." << endl;
    }
}
const int size=50;
struct Outfit{
    char name[size];
    char type[size];
    char color[size];
    char occasion[size];
};
struct HistoryNode{
    Outfit viewedOutfit;
    HistoryNode* next;
};
class History
{
    HistoryNode* top;
public:
    History() 
	{ 
		top = NULL; 
	}
    void addToHistory(const Outfit& outfit) 
	{
        HistoryNode* ptr=new HistoryNode;
        ptr->viewedOutfit=outfit;
        ptr->next=top;
        top=ptr;
    }
    void show() 
	{
        HistoryNode* temp=top;
        if (top==NULL) 
		{
            cout<<"Nothing to show."<<endl;
        } 
		else 
		{ cout<<"\n=== History of Outfits ===\n"<<endl;
            int count=1;
            while(temp!=NULL)
			{
                cout<<"Outfit "<<count++<<":"<<endl;
                cout<<"Name: "<<temp->viewedOutfit.name<<endl;
                cout<<"Type: "<<temp->viewedOutfit.type<<endl;
                cout<<"Color: "<<temp->viewedOutfit.color<<endl;
                cout<<"Occasion: "<<temp->viewedOutfit.occasion<<endl;
                cout<<"-------------------"<<endl;
                temp=temp->next;
            }
        }
    }
};
History history;
const int Top=5, Bottom=5, Outer=2, FootWear=2;
string summer_tops[Top]={"White T-shirt", "Black T-shirt", "Light blue shirt", "Tank top", "Polo shirt"};
string summer_bottoms[Bottom]={"Black jeans", "Blue jeans", "Shorts", "Khaki pants", "Chinos"};
string summer_foot[FootWear]={"Sneakers", "Sandals"};

string rainy_tops[Top]={"Dark hoodie", "Full-sleeve T-shirt", "Raincoat", "Windbreaker", "Sweatshirt"};
string rainy_bottoms[Bottom]={"Dark jeans", "Track pants", "Waterproof pants", "Black jeans", "Cargo pants"};
string rainy_outer[Outer]={"Rain jacket", "Windbreaker"};
string rainy_foot[FootWear]={"Waterproof shoes", "Rain boots"};

string winter_tops[Top]={"Sweater", "Full-sleeve shirt", "Thermal shirt", "Turtleneck", "Flannel shirt"};
string winter_bottoms[Bottom]={"Black jeans", "Wool trousers", "Corduroys", "Dark jeans", "Cargo pants"};
string winter_outer[Outer]={"Jacket", "Coat"};
string winter_foot[FootWear]={"Boots", "Leather shoes"};

string spring_tops[Top]={"Casual shirt", "Polo T-shirt", "Light sweater", "Denim shirt", "Linen shirt"};
string spring_bottoms[Bottom]={"Chinos", "Jeans", "Khakis", "Light pants", "Cotton trousers"};
string spring_foot[FootWear]={"Loafers", "Sneakers"};
struct UndoStack{
    Outfit data[size];
    int top;
};
UndoStack undoStack;
void initStack(UndoStack& s)
{
	s.top = -1; 
}
bool isEmpty(UndoStack& s) 
{ 
	return s.top==-1; 
}
bool isFull(UndoStack& s) 
{ 
	return s.top==size-1; 
}
void push(UndoStack& s, Outfit outfit)
{
	if(!isFull(s)) 
		s.data[++s.top]=outfit; 
	else 
		cout<<"closet is full!"<<endl; 
}
//file handling
void save_outfits(const Outfit& outfit)
{
	ofstream ofile("outfits.txt", ios::app);
	
	if(ofile.is_open())
	{
		ofile<<outfit.name<<endl;
		ofile<<outfit.type<<endl;
		ofile<<outfit.color<<endl;
		ofile<<outfit.occasion<<endl;
		ofile<<"_-----_"<<endl;
		
		ofile.close();
		cout<<"outfit saved to file"<<endl;
	}
	else
	{
		cout<<"error opening file"<<endl;
	}
}

void load_outfits()
{
	int count=0;
	

	ifstream ifile("outfits.txt");
	
	if(ifile.is_open())
	{
		Outfit outfit;
		string line;
		
		while(getline(ifile,line))
		{
			if(line=="_-----_") continue;
			
			strcpy(outfit.name, line.c_str());
			getline(ifile,line);
			strcpy(outfit.type, line.c_str());
			getline(ifile,line);
			strcpy(outfit.color, line.c_str());
			getline(ifile,line);
			strcpy(outfit.occasion, line.c_str());
			getline(ifile,line);
			
			history.addToHistory(outfit);
		}
		
		ifile.close();
		cout<<"Outfits loaded from file"<<endl;
		
	ifile.close();
	if(count>0)
		cout<<"Loaded"<<count<<"previous outfits from file."<<endl;
	}
	else
	cout<<"no file found"<<endl;
}
bool contains(string text, string word)
{
    for(int i=0;i<text.length();i++)
    {
        text[i]=tolower(text[i]);
    }
    for(int i=0;i<word.length(); i++)
    {
        word[i]=tolower(word[i]);
    }
	return text.find(word)!=-1;
}

bool isCompatible(string top, string bottom, string weather)
{
    if ((contains(top, "shirt" )||contains(top, "polo")) && (bottom=="track pants"||bottom=="shorts"))
        return false;

    if (weather =="rainy"&&contains(top,"light"))
        return false;

    if (weather=="summer"&&(contains(top,"sweater") || contains(top,"thermal")))
        return false;

    return true;
}
void recommend_Outfit(string weather, string preference) 
{
    string* tops=NULL;
    string* bottoms=NULL;
    string* outerwear=NULL;
    string* footwear=NULL;
    int tops_count=0, bottoms_count=0, outer_count=0, foot_count=0;
    if(weather=="summer") 
	{
		tops=summer_tops; 
		tops_count=Top; 
		bottoms=summer_bottoms; 
		bottoms_count=Bottom; 
		footwear=summer_foot; 
		foot_count=FootWear; 
		outer_count=0; 
	}
    else if(weather == "rainy") 
	{
		tops=rainy_tops; 
		tops_count=Top; 
		bottoms=rainy_bottoms; 
		bottoms_count=Bottom; 
		outerwear=rainy_outer; 
		outer_count=Outer; 
		footwear=rainy_foot; 
		foot_count=FootWear; 
	}
    else if(weather=="winter")
	{
		tops=winter_tops; 
		tops_count=Top; 
		bottoms=winter_bottoms; 
		bottoms_count=Bottom; 
		outerwear=winter_outer; 
		outer_count=Outer; 
		footwear=winter_foot; 
		foot_count=FootWear; 
	}
    else if(weather=="spring") 
	{
		tops=spring_tops; 
		tops_count=Top; 
		bottoms=spring_bottoms; 
		bottoms_count=Bottom; 
		footwear=spring_foot; 
		foot_count=FootWear; 
		outer_count=0;
	}
    else 
	{
		cout<<"Invalid weather condition!"<<endl; 
		return; 
	}
    cout<<"\n=== Generating Outfit for "<<weather<<" weather ===\n"<<endl;
    bool found=false;
    srand(time(0));
    for(int i=0; i<tops_count && !found; i++) 
	{
        for(int j=0; j<bottoms_count && !found; j++) 
		{
            if(isCompatible(tops[i], bottoms[j], weather)) 
			{
                Outfit recommended;
                string outfitName=tops[i]+", "+bottoms[j];
                if(outer_count>0 && (weather=="rainy" || weather=="winter")) 
				{
                    int outerIdx=rand()%outer_count;
                    outfitName=outerwear[outerIdx]+", "+outfitName;
                }

                if(foot_count>0)
				{
                    int footIdx=rand()%foot_count;
                    outfitName=outfitName+", "+footwear[footIdx];
                }
                strcpy(recommended.name, outfitName.c_str());
                strcpy(recommended.type,"Complete Outfit");
                strcpy(recommended.color,"Mixed");
                strcpy(recommended.occasion, weather.c_str());
                cout<<"Recommended Outfit:"<<endl<<recommended.name<<endl;
                push(undoStack, recommended);
                history.addToHistory(recommended);
                
                save_outfits(recommended);
                found=true;
            }
        }
    }
    if(!found) 
		cout<<"No suitable outfit found for the given criteria."<<endl;
}
void undo_Recommendation(UndoStack& s) 
{
    if(isEmpty(s)) 
		cout<<"Nothing to undo!"<<endl;
    else 
	{
        Outfit undo=s.data[s.top--];
        cout<<"Undo successful."<<endl;
        cout<<"Removed outfit: "<<undo.name<<endl;
    }
}
void show_History() 
{
	history.show(); 
}



int main() 
{
    initStack(undoStack);
    load_outfits();
    
    storeOutfits();
    SortSeason();
    int choice;
    string weather, preference;
    cout<<"=== OUTFIT RECOMMENDATION SYSTEM ==="<<endl;
    do{
        cout<<"\n--- MENU ---"<<endl;
        cout<<"1. Recommend Outfit"<<endl;
        cout<<"2. Undo Recommendation"<<endl;
        cout<<"3. Show History"<<endl;
        cout<<"4. Search Outfit by Season"<<endl;
        cout<<"5. Show the Fit-Check File"<<endl;
        cout<<"6. Exit Fit-Check"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice) 
		{
        case 1:
            cout<<"\nEnter Weather (summer/rainy/winter/spring): ";
            cin>>weather;
            cout<<"Enter Preference (casual/formal): ";
            cin>>preference;
            recommend_Outfit(weather, preference);
            break;
        case 2:
            undo_Recommendation(undoStack);
            break;
        case 3:
            show_History();
            break;
        case 4:
            {
              string season;
              cout<<"Enter season to search: ";
              cin>>season;
              SearchSeasonOutfits(season);
            }
            break;
        case 5:
        	cout<<"showing your file"<<endl;
        	load_outfits();
        	break;
        
        case 6:
            cout<<"Exiting program. Goodbye!"<<endl;
            exit(0);
            
        default:
            cout<<"Invalid choice! Please try again."<<endl;
        }
    }while(choice!=5);

    return 0;
}
