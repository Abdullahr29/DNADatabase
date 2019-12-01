#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class DNA_Sequence{ //class used to sort and analyse parts of the actual dna sequence in the file
public:
    vector<char> seq;//vector to store the full sequence from the file
    vector<int> regions;//vector to store the beginnings of different regions, both N and C, from the sequence
    int region;
    int n_regions;
    int c_regions;
    int pairs;
    int g_pairs=0;
    int a_pairs=0;
    int t_pairs=0;
    int c_pairs=0;
    int r_pairs=0;
    int y_pairs=0;
    int m_pairs=0;
    int k_pairs=0;
    int s_pairs=0;
    int w_pairs=0;
    int h_pairs=0;
    int b_pairs=0;
    int v_pairs=0;
    int d_pairs=0;
    int n_pairs=0;
    int u_pairs=0;

    DNA_Sequence();//default class constructor
    void setSequence(vector <char> seque);//sets sequence vector
    void setPairs(int pai);//sets pairs
    //void analyse(); ex-method to find and store the different regions, was too slow and required too much memory, therefore rendered useless
    void sort(char x);//function to sort each character into whatever base pair it is
    void setRegions();//sets the 3 region variables
};

DNA_Sequence::DNA_Sequence() = default;

void DNA_Sequence::setPairs(int pai) {
    pairs = pai;
}

void DNA_Sequence::sort(char x) {
    if(x == 'G'){
        g_pairs++;
    }
    else if(x == 'A'){
        a_pairs++;
    }
    else if(x == 'T'){
        t_pairs++;
    }
    else if(x == 'C'){
        c_pairs++;
    }
    else if(x == 'R'){
        r_pairs++;
    }
    else if(x == 'Y'){
        y_pairs++;
    }
    else if(x == 'M'){
        m_pairs++;
    }
    else if(x == 'K'){
        k_pairs++;
    }
    else if(x == 'S'){
        s_pairs++;
    }
    else if(x == 'W'){
        w_pairs++;
    }
    else if(x == 'H'){
        h_pairs++;
    }
    else if(x == 'B'){
        b_pairs++;
    }
    else if(x == 'V'){
        v_pairs++;
    }
    else if(x == 'D'){
        d_pairs++;
    }
    else if(x == 'N'){
        n_pairs++;
    }
    else{
        u_pairs++;
    }
}

/*
void DNA_Sequence::analyse() {
    int check = 0;
    int temp = 0;
    int index = 0;
    string store(seq.begin(),seq.end());
    while(check != -1){
        if(temp == 0){
            index = store.find("N");
            if(index == -1) {
                check = -1;
                regions.push_back(seq.size()-1);
            }
            else{
                regions.push_back(index);
            }
            temp = 1;
        }
        else if(temp == 1){
            index = store.find_first_not_of("N");
            if(index == -1) {
                check = -1;
                regions.push_back(seq.size()-1);
            }
            else{
                regions.push_back(index);
            }
            temp = 0;
        }
    }
    store.clear();
    region = regions.size()-1;
    setRegions();
}
*/

void DNA_Sequence::setSequence(vector<char> seque) {
    seq = seque;
}

void DNA_Sequence::setRegions() {
    region = regions.size() - 1;
    if(region%2 == 0){//if region vector length is even, equal number of N and C regions
        n_regions = region/2;
        c_regions = region/2;
    }
    else{//if region vector length is odd, one more N region than C region
        n_regions = (region-1)/2 + 1;
        c_regions = (region-1)/2;
    }
}


class DNA_DB{//class to store all the information of the file apart from the sequence, previously inherited DNA_Sequence object, however was less efficient therefore inheritance rendered useless
private:
    string file_name;
    string gid;
    string ref;
    string name;
public:
    DNA_DB(string filen, string gin, string refn, string namen);//constructor
    string getFile();//getter functions
    string getGid();
    string getRef();
    string getName();
};

DNA_DB::DNA_DB(string filen, string gin, string refn, string namen) {
    file_name = filen;
    gid = gin;
    ref = refn;
    name = namen;
}

string DNA_DB::getFile() {
    return file_name;
}

string DNA_DB::getGid() {
    return gid;
}

string DNA_DB::getRef() {
    return ref;
}

string DNA_DB::getName() {
    return name;
}

string file_in;//input string for all files entered
vector <string> files;//to store the seperated inputted files, only needed temporarily
vector <string> title;//to store the first line of the files, only needed temporarily
vector <DNA_DB> dna_db;//vector for all the different objects of the files
vector <DNA_Sequence> sequence;//vector for the sequences of all the loaded objects, all above vectors run in parallel
int valid_file = 0;//used to verify if files entered are valid
int check = 0;//used to check when quit option is selected
char choice = ' ';//used to keep track of choice of file to open

void input();//method used to take in user input for the files
void open_analyse();//method used to open the files, check their validity, and simultaneously extract key information for the sequence to increase efficiency
void load();//method used to load the data read from the files into separate object
//void analyse(); initial method used to extract data regarding regions to put in vector from DNA Sequence, required too much memory and ran far too slow, rendered useless, kept due emotional attachment
void menu();//first menu method
void submenu();//second menu method
void summary();//first menu summary
void help();//second menu help option
void sec_summary();//second menu summary
void gapReg(int reg);//second menu gap region option
void codReg(int reg);//second menu coded region option
void baseRange(const string& input);//second menu base range option
void dnaManInput(const string& input);//second menu manual dna search option
void dnaFilInput(const string& input);//second menu file input method


int main() {
    int file_check = 0;
    while(file_check == 0) {//runs until valid files are entered
        valid_file = 0;
        input();//files entered here
        open_analyse();//files opened,validated
        if(valid_file == 0){//checks if files were valid
            file_check = 1;
        }
        else{
            cout << "Invalid file name entered.\n";
        }
    }
    load();//loads valid files into objects
    //analyse(); archived function which was too slow
    menu();//initialises menu with all data loaded into objects
    cout << "Program Ended";
    return 0;
}

void input(){
    file_in = "";
    files.clear();
    sequence.clear();//clearing vectors and strings before input
    int check = 0;
    cout << "DNA Sequence Database Software \nSpecify the name of DNA sequence file names you would like to load. For\nmultiple files, add a ""','"" between each file name:\n>";
    cin >> file_in;

    while(check != -1){//runs until it finds more commas
        check = file_in.find(',');//finds comma
        files.push_back(file_in.substr(0,check));//gets everything from start of string to comma, which is the file
        file_in.erase(0,check+1);//erases everything before the comma which was just found
    }
    file_in.clear();//string deallocated to save memory
}

void open_analyse(){
    char x[400];//char array to store first line temporarily
    char y;//temporary char
    string ti;//temporary string
    int check = 0;
    int checker = 0;
    int counter = 0;
    vector <char> temp_seq;//temporary vector to hold sequence
    for(int i = 0; i < files.size(); i++){//runs for each file
        checker = 0;
        counter = 0;
        ifstream ist;//opens ifstream
        temp_seq.clear();
        cout << "Loading " << files[i] << "...\nPlease allow up to 1 minute to open the files\n";
        ist.open(files[i]);
        if(!ist){//checks validity of file, if invalid returns null
            valid_file = 1;
            return;
        }
        ist.getline(x,400,'\n');//gets first line
        ti = x;
        title.push_back(ti);//first line stored in vector
        DNA_Sequence obj;//sequence object declared
        while(ist >> y){//reads all other characters in file sequentially
            if(checker == 0){//checks if first character in sequence
                if(y == 'N'){
                    check = 0;//used to keep track of regions
                }
                else{
                    check = 1;
                }
                checker = 1;
                obj.regions.push_back(counter);//pushes back start of first region into regions vector in sequence object
            }
            else if(check == 0 && y != 'N'){//checks to find end of N region
                obj.regions.push_back(counter-1);
                check = 1;
            }
            else if(check == 1 && y == 'N'){//checks to find end of C region
                obj.regions.push_back(counter-1);
                check = 0;
            }
            temp_seq.push_back(y);//pushes back character by character
            obj.sort(y);//calls the object function to assign each character to base pair
            counter++;
        }
        obj.regions.push_back(counter);//adds final region to regions vector
        obj.setSequence(temp_seq);//sets sequence for object
        temp_seq.clear();//deallocation for memory
        obj.setRegions();//object function for regions
        //obj.analyse();//one of previous functions archived due to speed and efficiency
        sequence.push_back(obj);//vector to store the sequence objects
        sequence[i].setPairs(sequence[i].seq.size());//object function for pairs
        cout << "Successful loading of " << files[i] << "\n";
    }
}

void load(){
    int temp,temp2,len;
    string name,seq,gi,ref;
    for(int i = 0; i < files.size(); i++){//loops for each file and creates the object for each of them using the title vector
        temp = title[i].find("|");//all values found using find functions and temporary variables alternatingly
        temp2 = title[i].find("|",temp+1);
        len = temp2 - temp;
        gi = title[i].substr(temp+1,len-1);
        temp = title[i].find("|",temp2+1);
        temp2 = title[i].find("|",temp+1);
        len = temp2 - temp;
        ref = title[i].substr(temp+1, len-1);
        temp = title[i].find("H");
        name = title[i].substr(temp+0,-1);
        DNA_DB obj(files[i], gi, ref, name);//object created
        dna_db.push_back(obj);//object pushed back in vector (parallel to sequence vector)
    }
    title.clear();//deallocation for memory
    files.clear();//deallocation for memory
}

/*first method written to find and sort regions into vector, rendered useless
void analyse(){
    int check = 0;
    int size1 = dna_db.size();
    int size2;
    for(int i = 0; i < size1; i++){
        size2 = dna_db[i].getSeq().seq.size();
        for(int j = 0; j < size2; j++) {
            if(j == 0){
                dna_db[i].getSeq().regions.push_back(j);
            }
            else if(dna_db[i].getSeq().seq[j] != 'N' && check == 0) {
                check = 1;
                dna_db[i].getSeq().regions.push_back(j);
            }
            else if(dna_db[i].getSeq().seq[j] == 'N' && check == 1){
                check = 0;
                dna_db[i].getSeq().regions.push_back(j);
            }
            dna_db[i].getSeq().sort(dna_db[i].getSeq().seq[j]);
        }
        if(dna_db[i].getSeq().regions.size()%2 == 0){
            dna_db[i].getSeq().setN_reg(dna_db[i].getSeq().regions.size()/2);
            dna_db[i].getSeq().setC_reg(dna_db[i].getSeq().regions.size()/2-1);
        }
        else{
            dna_db[i].getSeq().setN_reg((dna_db[i].getSeq().regions.size()-1)/2);
            dna_db[i].getSeq().setC_reg((dna_db[i].getSeq().regions.size()-1)/2);
        }
        cout << dna_db[i].getSeq().g_pairs;

    }
}
*/

void menu(){//first menu
    check = 0;
    while(check == 0){
        cout << "Select one of the following options:\n";
        cout << "(S) Summary statistics of the DNA database\n";
        for(int i = 0; i < dna_db.size(); i++){
            cout << "(" << i+1 << ")" << " Analyse " << dna_db[i].getFile() << "\n";
        }
        cout << "(Q) Quit\n>";
        cin >> choice;
        if(choice == 'S'|| choice == 's'){//summary choice
            summary();
        }
        else if((choice - '0' >= 1 || choice - '0' <= dna_db.size()) && choice != 'Q'){//submenu choice
            submenu();
        }
        else if(choice == 'Q'|| choice == 'q'){//quit
            check = 1;
        }
        else{
            cout << "This choice is not available, please enter again";
        }
    }
}

void summary(){//prints relevant fields for each object
    for(int i = 0; i < dna_db.size(); i++){
        cout << "Sequence " << i+1 << ":\n";
        cout << "Name:\t" << dna_db[i].getName() << "\n";
        cout << "GID:\t" << dna_db[i].getGid() << "\n";
        cout << "REF:\t" << dna_db[i].getRef() << "\n";
        cout << "# base pairs:\t" << sequence[i].pairs << "\n";
    }
}

void submenu(){//second menu
    char sec_choice;//to keep track of second choice
    int sec_check = 0,reg;
    string input;
    while(check == 0 && sec_check == 0){
        cout << "\nSelect one of the following options for " << dna_db[(choice -'0')-1].getFile();
        cout << ":\n(H) Help\n(S) Summary statistics of the DNA sequence\n";
        cout << "(1) Analyse gap region\n(2) Analyse coded region\n";
        cout << "(3) Analyse base pair range\n(4) Find DNA sequence by manual input\n";
        cout << "(5) Find DNA sequence by file input\n";
        cout << "(R) Return to the previous menu\n(Q) Quit\n>";
        cin >> sec_choice;//input choice
        if(sec_choice == 'H' || sec_choice == 'h'){//help option
            help();
        }
        else if(sec_choice == 'S'|| sec_choice == 's'){//second summary option
            sec_summary();
        }
        else if(sec_choice == '1'){//to get chosen gap region
            cout << "\nEnter gap region number:\n>";
            cin >> reg;
            gapReg(reg);
        }
        else if(sec_choice == '2'){//to get chosen coded region
            cout << "\nEnter coded region number:\n>";
            cin >> reg;
            codReg(reg);
        }
        else if(sec_choice == '3'){//to get base pair range
            cout << "\nEnter a comma ',' separated base pair range:\n>";
            cin >> input;
            baseRange(input);
        }
        else if(sec_choice == '4'){//to get instances of the same nucleotide being found
            cout << "\nSpecify the DNA sequence nucleotides you would like to find:\n>";
            cin >> input;
            dnaManInput(input);
        }
        else if(sec_choice == '5'){//to load and search for a file
            cout << "\nSpecify the DNA sequence file you would like to find:\n>";
            cin >> input;
            dnaFilInput(input);
        }
        else if(sec_choice == 'R'|| sec_choice == 'r'){//return to previous menu
            sec_check = 1;
        }
        else if(sec_choice == 'Q'|| sec_choice == 'q'){//to quit
            check = 1;
        }
        else{
            cout << "This choice is not available, please enter again";
        }
    }
}

void help(){//the required help information
    cout << "Code Base Description\n"
            "G\tGuanine\n"
            "A\tAdenine\n"
            "T\tThymine (Uracil in RNA)\n"
            "C\tCytosine\n"
            "R\tPurine (A or G)\n"
            "Y\tPyrimidine (C or T or U)\n"
            "M\tAmino (A or C)\n"
            "K\tKetone (G or T)\n"
            "S\tStrong interaction (C or G)\n"
            "W\tWeak interaction (A or T)\n"
            "H\tNot-G (A or C or T) H follows G in the alphabet\n"
            "B\tNot-A (C or G or T) B follows A in the alphabet\n"
            "V\tNot-T (not-U) (A or C or G) V follows U in the alphabet\n"
            "D\tNot-C (A or G or T) D follows C in the alphabet\n"
            "N\tAny (A or C or G or T)\n";
}

void sec_summary(){//second summary option
    int i = (choice - '0') - 1;
    cout << "Sequence identifiers:\n";
    cout << "Name:\t" << dna_db[i].getName() << "\n";
    cout << "GID:\t" << dna_db[i].getGid() << "\n";
    cout << "REF:\t" << dna_db[i].getRef() << "\n";

    cout << "Region Characteristics:";
    cout << "\n# Regions:     "<< sequence[i].region;
    cout << "\n# N Regions:   " << sequence[i].n_regions;
    cout << "\n# C Regions:   "<< sequence[i].c_regions;

    cout << "\nBase Pair Characteristics";
    cout << "\n# base pairs:   " << sequence[i].pairs;
    cout << "\nG\t\t" << sequence[i].g_pairs;
    cout << "\nA\t\t" << sequence[i].a_pairs;
    cout << "\nT\t\t" << sequence[i].t_pairs;
    cout << "\nC\t\t" << sequence[i].c_pairs;
    cout << "\nR\t\t" << sequence[i].r_pairs;
    cout << "\nY\t\t" << sequence[i].y_pairs;
    cout << "\nM\t\t" << sequence[i].m_pairs;
    cout << "\nK\t\t" << sequence[i].k_pairs;
    cout << "\nS\t\t" << sequence[i].s_pairs;
    cout << "\nW\t\t" << sequence[i].w_pairs;
    cout << "\nH\t\t" << sequence[i].h_pairs;
    cout << "\nB\t\t" << sequence[i].b_pairs;
    cout << "\nV\t\t" << sequence[i].v_pairs;
    cout << "\nD\t\t" << sequence[i].d_pairs;
    cout << "\nN\t\t" << sequence[i].n_pairs;
    cout << "\nUnknown\t\t" << sequence[i].u_pairs;
}

void gapReg(int reg){//function to find and output specified gap region
    int start = 0;
    int end = 0;
    if(reg == 1){//if they ask for the first region, get start and end from regions vector from object
        start = sequence[(choice - '0')-1].regions[reg-1];
        end = sequence[(choice - '0')-1].regions[reg];
    }
    else if(reg > sequence[(choice - '0')-1].regions.size()/2){//check if region is nonexistent
        cout << "Invalid region";
        return;
    }
    else{//finds the start and end of region in all other cases
        start = sequence[(choice - '0')-1].regions[(reg*2)-2];
        end = sequence[(choice - '0')-1].regions[(reg*2)-1];
    }
    cout << "\nSelected sequence:";
    cout << "\nBase pair range: (" << start + 2 << "," << end + 1 << ")";
    cout << "\nGap region number: " << reg;
    cout << "\nSequence:\n";
    for(int i = start+1; i < end+1; i++){
        cout << sequence[(choice - '0')-1].seq[i];
    }
}

void codReg(int reg){//function to find specific coded region
    int start = 0;
    int end = 0;
    if(reg == 1){//if they ask for the first region, get start and end from regions vector from object
        start = sequence[(choice - '0')-1].regions[reg];
        end = sequence[(choice - '0')-1].regions[reg+1];
    }
    else if(reg > sequence[(choice - '0')-1].regions.size()/2){//checks if region is nonexistent
        cout << "Invalid region";
        return;
    }
    else{//finds all the other regions start and ends
        start = sequence[(choice - '0')-1].regions[(reg*2)-1];
        end = sequence[(choice - '0')-1].regions[reg*2];
    }
    cout << "\nSelected sequence:";
    cout << "\nBase pair range: (" << start + 2 << "," << end + 1<< ")";
    cout << "\nCoded region number: " << reg;
    cout << "\nSequence:\n";
    for(int i = start+1; i < end+1; i++){
        cout << sequence[(choice - '0')-1].seq[i];
    }
}

void baseRange(const string& input){//takes the string of input of their range
    int ind;
    ind = input.find(",");
    int start = stoi(input.substr(0,ind));//gets the start
    int end = stoi(input.substr(ind+1, -1));//gets the end
    if(start > sequence[(choice - '0')-1].seq.size() - 1|| start > sequence[(choice - '0')-1].seq.size() - 1){//checks invalid range
        cout << "Invalid range";
        return;
    }
    else {
        cout << "\nBase pair range: (" << start << "," << end << ")";
        cout << "\nSequence:\n";
        for (int i = start; i < end; i++) {
            cout << sequence[(choice - '0') - 1].seq[i];
        }
    }
}

void dnaManInput(const string& input){//takes sequence for input and finds instances
    string store(sequence[(choice - '0') - 1].seq.begin(),sequence[(choice - '0') - 1].seq.end());//converts sequence vector to a string for find function
    int index = 0;
    int counter = 0;
    if(store.find(input, index+1) != -1){
        cout << "\nMatching sequence found at:\n";
    }
    while(store.find(input, index+1) != -1) {//runs while it can find more sequences which match in the sequence file
        counter++;
        index = store.find(input, index + 1);//finds the starting positions sequentially
        if (index != -1) {//to ensure that it doesnt run an extra time
            cout << "\n" << counter << ".  Base pair range:  (" << index + 1 << "," << index + input.size() << ")\n";
            for (int i = index - 21; i < index; i++) {//previous 20 characters
                cout << sequence[(choice - '0') - 1].seq[i];
            }
            cout << "\n" << input << "\n";//input sequence
            for (int i = index + input.size(); i < index + input.size() + 21; i++) {//next 20 character
                cout << sequence[(choice - '0') - 1].seq[i];
            }
        }
    }
    store.clear();//deallocation to save memory
    if(counter == 0){//checker for non existent sequence
        cout << "No such DNA sequence found in file";
    }
}

void dnaFilInput(const string& input){//takes file as input to search for
    char x[400];
    char y;
    string temp_seq;
    ifstream ist;//used to open the file
    cout << "\nLoading " << input << "...\n";
    ist.open(input);//opens file
    if(!ist){//checks file is valid
        cout << "Invalid file uploaded";
        return;
    }
    ist.getline(x,400,'\n');//gets first line to remove from ifstream
    while(ist >> y){//loads file in string
        temp_seq = temp_seq + y;
    }
    cout << "Successful loading of " << input << "\n";
    dnaManInput(temp_seq);//sends string to function which searches for strings
    temp_seq.clear();//cleared for deallocation
}




