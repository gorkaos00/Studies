#include <iostream>
#include <math.h>

void CRCCheck(int BinArr[], int n, std::string divider, std::string filename);

std::basic_string<char> FileInput(int *count, std::string filename){
    FILE *inputFileHandle = fopen(filename.c_str(),"rb");
    std::string text;
    unsigned char buffer[1];
    int readBytesLength=1;
    while(fread(buffer,sizeof(unsigned char),readBytesLength,inputFileHandle)) {
        text.append(sizeof(buffer[0]),buffer[0]);
        (*count)++;
    }
    std::cout<<"Input File in ASCII:"<<std::endl<<text<<std::endl;
    fclose(inputFileHandle);
    return text;
}
void CRCCalculate(int BinArr1[],int n, std::string divider,std::string filename){
    std::string divider2=divider;
    int div[divider.length()];
    int length=divider.length();
    for(int i=0;i<length;i++){
        div[i]=divider.at(0)-48;
        divider.erase(0,1);
    }
    int count=n+length-1;
    int BinArr[count];
    for(int i=0;i<count;i++){
        if(i>=n){
            BinArr[i]=0;
        }else {
            BinArr[i] = BinArr1[i];
        }
    }
    std::string result;
    std::string remainder;
    for(int i=0;i<n;i++) {
            if (BinArr[i] == 1) {
                result.append(1, '1');
                for (int j = 0; j < length; j++) {
                    if (BinArr[i + j] == div[j]) {
                        BinArr[i + j] = 0;
                    } else {
                        BinArr[i + j] = 1;
                    }
                }
            } else {
                result.append(1, '0');

                for (int j = 0; j < length; j++) {
                    if (BinArr[i + j] == 0) {
                        BinArr[i + j] = 0;
                    } else {
                        BinArr[i + j] = 1;
                    }
                }
            }
             if (i == n-1) {
                 for (int j = 0; j < length-1; j++) {
                     char k=BinArr[n + j] + 48;
                     remainder.append(1, k);
                 }
             }
    }
    while(result.at(0)-48!=1){
        result.erase(0,1);
    }
std::cout<<"Remainder="<<remainder<<std::endl;
int n1;
n1=n+remainder.length();
    int BinArr2[n1];
    for(int i=0;i<n1;i++){
        if(i<n) {
            BinArr2[i] = BinArr1[i];
        }
        else{
            BinArr2[i]=remainder.at(0)-48;
            remainder.erase(0,1);

        }
    }
    n=n1;
    int AsciArr[n/8+1];
    for(int i=0;i<(n/8)+1;i++){
        AsciArr[i]=0;
    }
    int x=8,y=0;
    for(int i=1;i<n+1;i++) {
        x--;
        if(BinArr2[i-1]==1) {
            AsciArr[y] += pow(2, x);
        }
        if(i%8==0) {
            x = 8;
            y++;
        }
    }

    FILE *outputFileHandle=fopen(filename.c_str(),"w");
    if(outputFileHandle==NULL){
        std::cout<<"Nie udalo sie otworzyc pliku"<<filename<<"do zapisu"<<std::endl;
    }
    else{
        int i=0;
        char cos[1];

        while(i<(n/8+1)){
            cos[0]=AsciArr[i];
            fprintf(outputFileHandle,"%c",cos[0]);
            i++;
        }
    }
    fclose(outputFileHandle);
    std::cout<<"CRC added to the file."<<std::endl<<std::endl;
}
void CRCCheck(int BinArr1[], int n, std::string divider, std::string filename) {
    std::string divider2=divider;
    int div[divider.length()];
    int length=divider.length();
    for(int i=0;i<length;i++){
        div[i]=divider.at(0)-48;
        divider.erase(0,1);
    }
    int count=n+length-1;
    int BinArr[count];
    for(int i=0;i<count;i++){
        if(i>=n){
            BinArr[i]=0;
        }else {
            BinArr[i] = BinArr1[i];
        }
    }
    std::string result;
    std::string remainder;
    for(int i=0;i<n;i++) {
        if (BinArr[i] == 1) {
            result.append(1, '1');
            for (int j = 0; j < length; j++) {
                if (BinArr[i + j] == div[j]) {
                    BinArr[i + j] = 0;
                } else {
                    BinArr[i + j] = 1;
                }
            }
        } else {
            result.append(1, '0');

            for (int j = 0; j < length; j++) {
                if (BinArr[i + j] == 0) {
                    BinArr[i + j] = 0;
                } else {
                    BinArr[i + j] = 1;
                }
            }
        }
        if (i == n-1) {
            for (int j = 0; j < length-1; j++) {
                char k=BinArr[n + j] + 48;
                remainder.append(1, k);
            }
        }
    }
    while(result.at(0)-48!=1){
        result.erase(0,1);
    }
    std::cout<<"Remainder="<<remainder<<std::endl;
    int check=0;
    n=remainder.length();
    for(int i=0;i<n;i++){
        if(remainder.at(0)-48==1){
            check=1;
        }
        remainder.erase(0,1);
    }
    if(check==0){
        std::cout<<"CRC is correct"<<std::endl<<std::endl;
    }else{
        std::cout<<"File is corrupted"<<std::endl<<std::endl;
    }

}






int main() {
    int x = 1;
    while (x != 3) {
        std::cout << "1.Calculate CRC\n2.Check CRC\n3.Exit" << std::endl << "Your choice:";
        std::cin >> x;
        switch (x) {
            case 1 : {
                std::string text;
                int count = 0, b;
                std::cout << "Enter the filename:" << std::endl;
                std::string filename;
                std::cin >> filename;
                std::cout << "Enter the key:" << std::endl;
                std::string divider;
                std::cin >> divider;
                text = FileInput(&count, filename);
                int n = count * 8;
                int BinArr[n];
                for (int i = 0; i < count; i++) {
                    int bin = text.at(0);
                    int k = 7;
                    for (int j = 0; j < 8; j++) {
                        int a;
                        a = j + k;

                        b = bin / (pow(2, a));
                        if (b == 1) {
                            BinArr[j + i * 8] = 1;
                            bin = bin - pow(2, a);

                        } else {
                            BinArr[j + i * 8] = 0;
                        }

                        k = k - 2;
                    }
                    text.erase(0, 1);
                }
                std::cout << "Input File in binary: " << std::endl;
                for (int i = 0; i < n; i++) {
                    std::cout << BinArr[i];
                }
                std::cout << std::endl<<std::endl<<std::endl;
                CRCCalculate(BinArr, n, divider, filename);
                break;
            }
            case 2: {
                std::string text;
                int count = 0, b;
                std::cout << "Enter the filename:" << std::endl;
                std::string filename;
                std::cin >> filename;
                std::cout << "Enter the key:" << std::endl;
                std::string divider;
                std::cin >> divider;
                text = FileInput(&count, filename);
                int n = count * 8;
                int BinArr[n];
                for (int i = 0; i < count; i++) {
                    int bin = text.at(0);
                    if(text.at(0)<0){
                        bin=256+text.at(0);
                    }
                    int k = 7;
                    for (int j = 0; j < 8; j++) {
                        int a;
                        a = j + k;

                        b = bin / (pow(2, a));
                        if (b == 1) {
                            BinArr[j + i * 8] = 1;
                            bin = bin - pow(2, a);

                        } else {
                            BinArr[j + i * 8] = 0;
                        }

                        k = k - 2;
                    }
                    text.erase(0, 1);
                }
                std::cout << "Input File in binary: " << std::endl;
                for (int i = 0; i < n; i++) {
                    std::cout << BinArr[i];
                }
                std::cout << std::endl<<"Checking CRC..."<<std::endl<<std::endl;
                CRCCheck(BinArr, n, divider, filename);
                break;
            }
            case 3 :
                return 0;
        }
    }

}

