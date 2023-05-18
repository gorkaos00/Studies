#include <iostream>
#include <cstdlib>
#include<list>
#include <cstring>
#include <math.h>

struct HuffmanNode{
    int symbol;
    int frequency;

};typedef HuffmanNode Huff;

struct HuffmanTree{

    int symbol;
    int frequency;
    struct HuffmanTree *parent;
    struct HuffmanTree *L;
    struct HuffmanTree *P;
}; typedef HuffmanTree HuffT;

struct Code{
    int symbol;
    std::string code;
};typedef Code Code;


int CompareHuffman(const void *item1,const void *item2);


int GenerateModelFromFile(Huff HuffArray[256]){
    FILE *inputFileHandle = fopen("test.txt","rb");
    int count=0;
    int ReadCount=0;
    unsigned char buffer[1];
    int readBytesLength=1;
    while(ReadCount=fread(buffer,sizeof(unsigned char),readBytesLength,inputFileHandle)) {
        HuffArray[buffer[0]].symbol=buffer[0];
        HuffArray[buffer[0]].frequency++;
        count++;

    }
    fclose(inputFileHandle);
    return count;
}
void SortModel(int count,Huff HuffArray[]){
    qsort(HuffArray, count, sizeof(HuffArray), reinterpret_cast<int (*)(const void *, const void *)>(CompareHuffman));

}
int CompareHuffman(const void *item1,const void *item2){
    Huff *node1=(Huff*)item1;
    Huff *node2=(Huff*)item2;
    int result=(node1->frequency-node2->frequency);
    return -result;
}

void WriteModelToFile(int length,int count,Huff HuffArray[]){
    char filename[]="modelsort.txt";
    FILE *outputFileHandle=fopen(filename,"w");
    if(outputFileHandle==NULL){
        std::cout<<"Nie udalo sie otworzyc pliku"<<filename<<"do zapisu"<<std::endl;
    }
    else{
        int i=0;
        fprintf(outputFileHandle,"%d\n",count);
        while(i<length){
            fprintf(outputFileHandle,"%d:%d\n",HuffArray[i].symbol,HuffArray[i].frequency);
            i++;
        }
    }
    fclose(outputFileHandle);
}


void GenerateHuffmanTree(int length, HuffmanNode HuffArray[], HuffmanTree **first) {


    int a=0;
    HuffT *node=NULL;
    HuffT *list[length];
    HuffT *node2=NULL;

    int count=0;
    int i=length-1;
    while(i>=0) {

        if(count==1){

            node2=NULL;
            node=list[0];
        }
        if(count ==2){
            node=list[0];
            node2=list[1];
        }
        if (count > 2) {
            node=list[0];
            node2=list[1];
        for (int j = 0; j < count; j++) {

            if (node->frequency > list[j]->frequency) {
                node = list[j];
                if(node==node2){

                    node2=list[0];
                }
            }
        }
        for (int j = 0; j < count; j++) {
            if (node2->frequency> list[j]->frequency && list[j] != node) {
                node2 = list[j];
            }
        }


    }
        if(node2!=NULL) {
            if (node->frequency + HuffArray[i].frequency <= HuffArray[i].frequency + HuffArray[i - 1].frequency
                && node->frequency + node2->frequency >= node->frequency + HuffArray[i].frequency && i != 0
                    ) {
                HuffT *newe = new(HuffT);
                newe->frequency = HuffArray[i].frequency;
                newe->symbol = HuffArray[i].symbol;
                newe->L = NULL;
                newe->P = NULL;
                HuffT *parent = new(HuffT);
                parent->symbol = 1000 + a;
                parent->frequency = node->frequency + newe->frequency;
                parent->L = node;
                parent->P = newe;
                node->parent = parent;
                newe->parent = parent;
                for (int j = 0; j < count; j++) {
                    if (list[j] == node) {
                        list[j] = parent;
                    }
                }

                node = parent;
                i--;
                a++;
            } else if (
                    node->frequency + HuffArray[i].frequency >= HuffArray[i].frequency + HuffArray[i - 1].frequency &&
                    HuffArray[i].frequency + HuffArray[i - 1].frequency <= node->frequency + node2->frequency &&
                    i != 0) {

                HuffT *newe = new(HuffT);
                HuffT *nowy = new(HuffT);
                newe->frequency = HuffArray[i].frequency;
                newe->symbol = HuffArray[i].symbol;
                newe->L = NULL;
                newe->P = NULL;
                nowy->frequency = HuffArray[i - 1].frequency;
                nowy->symbol = HuffArray[i - 1].symbol;
                nowy->L = NULL;
                nowy->P = NULL;
                HuffT *parent = new(HuffT);
                parent->symbol = 1000 + a;
                parent->frequency = nowy->frequency + newe->frequency;
                parent->L = nowy;
                parent->P = newe;
                nowy->parent = parent;
                newe->parent = parent;

                list[count] = parent;
                count++;
                i -= 2;
                a++;
            }else if(node->frequency + HuffArray[i].frequency >= node->frequency + node2->frequency &&
                     HuffArray[i].frequency + HuffArray[i - 1].frequency >= node->frequency + node2->frequency &&
                     i != 0){
                HuffT *parent = new(HuffT);
                parent->L = node;
                parent->P = node2;
                parent->symbol = 1000 + a;
                parent->frequency = node->frequency + node2->frequency;
                parent->parent = NULL;
                node->parent = parent;
                node2->parent = parent;
                for (int j = 0; j < count; j++) {
                    if (list[j] == node) {
                        list[j] = parent;

                    }
                }
                int b=0;
                for(int j=0;j<count;j++){
                    if(list[j]==node2){

                        b=1;
                    }
                    if(b==1){
                        list[j]=list[j+1];
                    }
                }


                count--;
                a++;

            }
            else if (i == 0) {
                if (node->frequency + HuffArray[i].frequency < node->frequency + node2->frequency) {
                    HuffT *newe = new(HuffT);
                    newe->frequency = HuffArray[i].frequency;
                    newe->symbol = HuffArray[i].symbol;
                    newe->L = NULL;
                    newe->P = NULL;
                    HuffT *parent = new(HuffT);
                    parent->symbol = 1000 + a;
                    parent->frequency = node->frequency + newe->frequency;
                    parent->L = node;
                    parent->P = newe;
                    node->parent = parent;
                    newe->parent = parent;
                    for (int j = 0; j < count; j++) {
                        if (list[j] == node) {
                            list[j] = parent;
                        }
                    }


                    node = parent;
                    i--;
                    a++;
                } else {
                    HuffT *parent = new(HuffT);
                    parent->L = node;
                    parent->P = node2;
                    parent->symbol = 1000 + a;
                    parent->frequency = node->frequency + node2->frequency;
                    parent->parent = NULL;
                    node->parent = parent;
                    node2->parent = parent;
                    for (int j = 0; j < count; j++) {
                        if (list[j] == node) {
                            list[j] = parent;

                        }
                    }
                    int b = 0;
                    for (int j = 0; j < count; j++) {
                        if (list[j] == node2) {

                            b = 1;
                        }
                        if (b == 1) {
                            list[j] = list[j + 1];
                        }
                    }


                    count--;
                    a++;
                }
            }
        }

        else if(node!=NULL) {
            if (node->frequency + HuffArray[i].frequency <= HuffArray[i].frequency + HuffArray[i - 1].frequency
                    ) {

                HuffT *newe = new(HuffT);

                newe->frequency = HuffArray[i].frequency;
                newe->symbol = HuffArray[i].symbol;
                newe->L = NULL;
                newe->P = NULL;
                HuffT *parent = new(HuffT);
                parent->symbol = 1000 + a;
                parent->frequency = node->frequency + newe->frequency;
                parent->L = node;
                parent->P = newe;
                node->parent = parent;
                newe->parent = parent;
                list[0] = parent;


                node = parent;

                i--;
                a++;
            } else if (node->frequency + HuffArray[i].frequency >= HuffArray[i].frequency + HuffArray[i - 1].frequency &&
                       i != 0) {
                HuffT *newe = new(HuffT);
                HuffT *nowy = new(HuffT);
                newe->frequency = HuffArray[i].frequency;
                newe->symbol = HuffArray[i].symbol;
                newe->L = NULL;
                newe->P = NULL;
                nowy->frequency = HuffArray[i - 1].frequency;
                nowy->symbol = HuffArray[i - 1].symbol;
                nowy->L = NULL;
                nowy->P = NULL;
                HuffT *parent = new(HuffT);
                parent->symbol = 1000 + a;
                parent->frequency = nowy->frequency + newe->frequency;
                parent->L = nowy;
                parent->P = newe;
                nowy->parent = parent;
                newe->parent = parent;



                list[count] = parent;
                node = parent;

                count++;
                i -= 2;
                a++;
            } else if (i == 0) {
                    HuffT *newe = new(HuffT);
                    newe->frequency = HuffArray[i].frequency;
                    newe->symbol = HuffArray[i].symbol;
                    newe->L = NULL;
                    newe->P = NULL;
                    HuffT *parent = new(HuffT);
                    parent->symbol = 1000 + a;
                    parent->frequency = node->frequency + newe->frequency;
                    parent->L = node;
                    parent->P = newe;
                    node->parent = parent;
                    newe->parent = parent;
                    for (int j = 0; j < count; j++) {
                        if (list[j] == node) {
                            list[j] = parent;
                        }
                    }



                    node = parent;
                    i--;
                    a++;

            }
        }
        else{
            HuffT *newe = new(HuffT);
            HuffT *nowy = new(HuffT);
            newe->frequency = HuffArray[i].frequency;
            newe->symbol = HuffArray[i].symbol;
            newe->L = NULL;
            newe->P = NULL;
            nowy->frequency = HuffArray[i - 1].frequency;
            nowy->symbol = HuffArray[i - 1].symbol;
            nowy->L = NULL;
            nowy->P = NULL;
            HuffT *parent = new(HuffT);
            parent->symbol = 1000 + a;
            parent->frequency = nowy->frequency + newe->frequency;
            parent->L = nowy;
            parent->P = newe;
            nowy->parent = parent;
            newe->parent = parent;


            node=parent;
            list[count] = parent;

            count++;
            i -= 2;
            a++;

        }
    }
    while(count>1){

        if (count >= 2) {

            node = list[0];
            node2 = list[1];
            for (int j = 0; j < count; j++) {
                if (node->frequency >= list[j]->frequency) {
                    node = list[j];
                }
            }
            if(node2==node){
                node2=list[0];
            }
            for (int j = 0; j < count; j++) {
                if (node2->frequency >= list[j]->frequency && list[j] != node) {
                    node2 = list[j];
                }
            }

        }


        HuffT *parent = new(HuffT);
        parent->L = node;
        parent->P = node2;
        parent->symbol = 1000 + a;
        parent->frequency = node->frequency + node2->frequency;
        parent->parent = NULL;
        node->parent = parent;
        node2->parent = parent;
        for (int j = 0; j < count; j++) {
            if (list[j] == node) {
                list[j] = parent;

            }
        }
        int b=0;
        for(int j=0;j<count;j++){
            if(list[j]==node2){

                b=1;
            }
            if(b==1){
                list[j]=list[j+1];
            }
        }


        count--;
        a++;
    }
    *first=list[0];



}


void WriteHuffmanTree(HuffT Array[],int length) {
    char filename[]="tree_graf.txt";
    FILE *outputFileHandle=fopen(filename,"w");
    HuffT *node;
    if(outputFileHandle==NULL){
        std::cout<<"Nie udalo sie otworzyc pliku"<<filename<<"do zapisu"<<std::endl;
    }
    else{
        for(int i=0;i<length;i++) {
            if(Array[i].symbol>256) {
                fprintf(outputFileHandle, "#%d:%d\t",Array[i].symbol,Array[i].frequency);
                if(Array[i].L!=NULL) {
                    node = Array[i].L;
                    fprintf(outputFileHandle, "ChildLeft:%d\t", node->symbol);
                } else{
                    fprintf(outputFileHandle, "ChildLeft:none\t");
                }
                if(Array[i].P!=NULL) {
                node=Array[i].P;
                fprintf(outputFileHandle, "ChildRight:%d\t",node->symbol);
                } else{
                    fprintf(outputFileHandle, "ChildRight:none\t");
                }
                if(Array[i].parent!=NULL) {
                node=Array[i].parent;
                fprintf(outputFileHandle, "Parent:%d\n",node->symbol);
                } else{
                    fprintf(outputFileHandle, "Parent:none\n");
                }

            }
            else{
                fprintf(outputFileHandle, "%d:%d\t",Array[i].symbol,Array[i].frequency);
                if(Array[i].L!=NULL) {
                    node = Array[i].L;
                    fprintf(outputFileHandle, "ChildLeft:%d\t", node->symbol);
                } else{
                    fprintf(outputFileHandle, "ChildLeft:none\t");
                }
                if(Array[i].P!=NULL) {
                    node=Array[i].P;
                    fprintf(outputFileHandle, "ChildRight:%d\t",node->symbol);
                } else{
                    fprintf(outputFileHandle, "ChildRight:none\t");
                }
                if(Array[i].parent!=NULL) {
                    node=Array[i].parent;
                    fprintf(outputFileHandle, "Parent:%d\n",node->symbol);
                } else{
                    fprintf(outputFileHandle, "Parent:none\n");
                }
            }
        }
    }
    fclose(outputFileHandle);
}

void TreeToArray(HuffT *node, HuffmanTree Array[],int *i) {



        Array[*i].frequency=node->frequency;
        Array[*i].symbol=node->symbol;
        Array[*i].parent=node->parent;
        Array[*i].L=node->L;
        Array[*i].P=node->P;
        (*i)++;
    if(node->L!=NULL){TreeToArray(node->L,Array,i);}
    if(node->P!=NULL){TreeToArray(node->P,Array,i);}
    return;

}

void TreeCode(HuffT *node, Code Array[],int *i, std::string code) {
    if(node->symbol<256){
        Array[*i].symbol=node->symbol;
        Array[*i].code=code;
        (*i)++;
    }
    if(node->L!=NULL){TreeCode(node->L,Array,i,code+"0");}
    if(node->P!=NULL){TreeCode(node->P,Array,i,code+"1");}
    return;

}

void WriteCodetoFile(Code Array[], int length) {
    char filename[]="tree_code.txt";
    FILE *outputFileHandle=fopen(filename,"w");
    if(outputFileHandle==NULL){
        std::cout<<"Nie udalo sie otworzyc pliku"<<filename<<"do zapisu"<<std::endl;
    }
    else{
        fprintf(outputFileHandle,"%d\n",length);
        for(int i=0;i<length;i++){

            fprintf(outputFileHandle,"%d-%s\n",Array[i].symbol,Array[i].code.c_str());
        }
    }
    fclose(outputFileHandle);

}

void WriteCompressedFile(Code Array[], int lengthofarray) {
    char filename[] = "tree";
    FILE *outputFileHandle = fopen(filename, "w");
    if (outputFileHandle == NULL) {
        std::cout << "Nie udalo sie otworzyc pliku" << filename << "do zapisu" << std::endl;
    }
    else{
        int ReadCount=0;
        unsigned char buffer[1];
        int readBytesLength=1;
        int value=0,rest;
        int bytes=7;
        char text;
        int c;
        FILE *inputFileHandle = fopen("test.txt","rb");
        while(ReadCount=fread(buffer,sizeof(unsigned char),readBytesLength,inputFileHandle)) {
           for(int i=0;i<=lengthofarray;i++){
               if(buffer[0]==Array[i].symbol){
                   for(int j=0;j<Array[i].code.size();j++){
                       if(Array[i].code[j]=='1') {
                           value += pow(2,bytes);
                       }
                       if(bytes==0){
                           fprintf(outputFileHandle,"%c",value);
                           value=0;
                           bytes=8;

                       }
                       bytes--;
                   }
               }
           }
        }

        if(bytes!=0) {

                value += pow(2,bytes);

        }
        fprintf(outputFileHandle,"%c",value);


        fclose(inputFileHandle);
        fclose(outputFileHandle);

    }

}

void ReadCodeTablefromFile(Code Array[]) {
    FILE *inputFileHandle = fopen("tree_code.txt","rb");
    unsigned char buffer[1];
    int i=0,a=0,b=0,c=0;
    while(fread(buffer,sizeof(unsigned char),1,inputFileHandle)){

        if(buffer[0]=='-'){

            a=1;
            c=0;
        }
        else if(buffer[0]=='\n'){

            a=0;
            if(b==1){
                i++;
            }
            b=1;
            c=0;
        }
        else if(a==0 && b==1 ){

            Array[i].symbol=Array[i].symbol*10*c+(buffer[0]-48);
            c=1;
        }
        else if(a==1 && b==1){



            if(c==0) {


                Array[i].code = buffer[0];
                c=1;
            }
            else{

                Array[i].code += buffer[0];
            }
        }

    }
    fclose(inputFileHandle);

}

int Readlength() {
    FILE *inputFileHandle = fopen("tree_code.txt","rb");
    int n=0;
    unsigned char buffer[1];
    int c=0;

    while(fread(buffer,sizeof(unsigned char),1,inputFileHandle)) { ;
        if (buffer[0] == 13) {
            fclose(inputFileHandle);
            return n;
        }
        n=n*c*10+(buffer[0] - 48);
        c=1;
    }
}

void WriteDecompressedFile(Code Array[], int lengthofdecode) {
    char filename[] = "test.txt.decompressed";
    char filename2[] = "tree";
    FILE *outputFileHandle = fopen(filename, "w");
    FILE *inputFileHandle = fopen(filename2, "rb");
    if (outputFileHandle == NULL) {
        std::cout << "Nie udalo sie otworzyc pliku" << filename << "do zapisu" << std::endl;
    }
    else{
        unsigned char buffer[0];
        std::string code;
        int value;
        code.clear();
        while(fread(buffer,sizeof(unsigned char),1,inputFileHandle)) {

            value=buffer[0];
            for (int j = 7; j >=0; j--) {
                if(buffer[0]/128==1){
                    code+='1';
                }
                else{
                code+='0';
                }
                buffer[0]=buffer[0]<<1;

                for (int i = 0; i < lengthofdecode; i++) {
                    if (code == Array[i].code) {

                        fprintf(outputFileHandle, "%c",Array[i].symbol);
                        code.clear();
                        value=0;
                    }
                }
            }
		}
        
    }
    fclose(inputFileHandle);
    fclose(outputFileHandle);

}

int main() {
	int n=0;
	while(n!=3) {
        std::cout << "Wybierz metode dzialania\n[1]Kompresja\n[2]Dekompresja\n[3]Wyjscie\nWybor:";
        std::cin >> n;

        if (n == 1) {
            std::cout << "Plik wejsciowy: test.txt" << std::endl;
            std::cout << "Plik wyjsciowy: tree" << std::endl;
            int count;
            Huff HuffArraytest[256];

            for (int i = 0; i < 256; i++) {
                HuffArraytest[i].frequency = 0;
                HuffArraytest[i].symbol = 0;
            }
            count = GenerateModelFromFile(HuffArraytest);
            Huff HuffArray[256];
            int lengthofarray = 0;
            for (int i = 0; i < 256; i++) {
                if (HuffArraytest[i].frequency == 0) {
                } else {
                    HuffArray[lengthofarray].symbol = HuffArraytest[i].symbol;
                    HuffArray[lengthofarray].frequency = HuffArraytest[i].frequency;
                    lengthofarray++;
                }
            }
            SortModel(lengthofarray, HuffArray);
            WriteModelToFile(lengthofarray, count, HuffArray);
            std::cout << "Model zrodla zostal zapisany do pliku" << std::endl;
            HuffT *first = NULL;
            GenerateHuffmanTree(lengthofarray, HuffArray, &first);
            HuffT Array[2 * lengthofarray];
            for (int i = 0; i < 2 * lengthofarray; i++) {
                Array[i].symbol = 0;
            }
            int i = 0;
            int length;
            TreeToArray(first, Array, &i);
            for (int i = 0; i < 2 * lengthofarray; i++) {
                if (Array[i].symbol == 0) {
                    length = i;
                    break;
                }
            }

            WriteHuffmanTree(Array, length);
            Code Arraycode[lengthofarray];
            std::string code;
            i = 0;
            TreeCode(first, Arraycode, &i, code);
            std::cout << "Drzewo kodowania + tablica kododwa zostaly zapisane do pliku" << std::endl;
            WriteCodetoFile(Arraycode, lengthofarray);

            WriteCompressedFile(Arraycode, lengthofarray);
            std::cout << "Kompresja zakonczona" << std::endl;

        } else if (n == 2) {
            std::cout << "Plik wejsciowy: tree" << std::endl;
            std::cout << "Plik wyjsciowy: test.txt.decompressed" << std::endl;
            int lengthofdecode = Readlength();
            Code Arraydecode[lengthofdecode];
            ReadCodeTablefromFile(Arraydecode);
            for (int i = 0; i < lengthofdecode; i++) {
                Arraydecode[i].code.resize(Arraydecode[i].code.size() - 1);
            }
            WriteDecompressedFile(Arraydecode, lengthofdecode);
        }
    }
    return 0;
}

