#include <iostream>

#include <fstream>


class imageProccessing {
private:

    int numRowsImg, numColsImg, minImg, maxImg, numRowsStructElem, numColsStructElem, minStrctElem, maxStrctElem, rowOrigin, colOrigin, rowFrameSize, colFrameSize;
    int origin, framedArrRows, framedArrCols, structuredPixCount;

    imageProccessing() {}

public:

    int **imgAry, **morphAry, **structElemAry,**tempArr;
    int neighborAry[9];
    int *structuredpixels;


    imageProccessing(int *values, int *sHeader) {

        numRowsImg = values[0];
        numColsImg = values[1];

        minImg = values[2];
        maxImg = values[3];
        numRowsStructElem = sHeader[0];
        numColsStructElem = sHeader[1];
        minStrctElem = sHeader[2];
        maxStrctElem = sHeader[3];
        rowOrigin = sHeader[4];
        colOrigin = sHeader[5];
        origin = (rowOrigin * numColsStructElem) + colOrigin;
        rowFrameSize = numRowsImg / 2;
        colFrameSize = numColsImg / 2;
        framedArrRows = numRowsImg + (rowFrameSize * 2);
        framedArrCols = numColsImg + (colFrameSize * 2);
        imgAry = new int *[framedArrRows];
tempArr=new int *[framedArrRows];
        morphAry = new int *[framedArrRows];

        for (int i = 0; i < framedArrRows; i++) {

            morphAry[i] = new int[framedArrCols];
            tempArr[i] = new int[framedArrCols];
            imgAry[i] = new int[framedArrCols];
        }

        structElemAry = new int *[numRowsStructElem];


        for (int i = 0; i < numRowsStructElem; i++) {


            structElemAry[i] = new int[numColsStructElem];
        }


    }

    ~imageProccessing() {
        for (int i = 0; i <framedArrRows; i++) {
delete [] tempArr[i];
            delete[]  imgAry[i];
            delete[] morphAry[i];
        }
        for (int i = 0; i < numRowsStructElem; i++) {


            delete[] structElemAry[i];
        }

delete [] tempArr;
        delete[] imgAry;
        delete[] morphAry;
        delete[] structElemAry;
        delete[] structuredpixels;

    }


    int location(int i, int j) {

        return (i * (framedArrCols)) + j;


    }

    bool check(int imgLoc) {
        //std::cout << "location  is x " << getRow(imgLoc)<< " next location is y" << getCol(imgLoc)<<std::endl;

        for (int i = 0; i < structuredPixCount; i++) {
int tempLoc=imgLoc;

int rowDiff=(structuredpixels[i]/numColsStructElem)-(origin/numColsStructElem);
int colDiff=(structuredpixels[i]%numColsStructElem)-(origin%numColsStructElem);
//std::cout << "location  is x " << getRow(imgLoc)+rowDiff<< " next location is y" <<getCol(imgLoc)+colDiff<<std::endl;
tempLoc=location(getRow(imgLoc)+rowDiff,getCol(imgLoc)+colDiff);
            //std::cout << "location  is x " << getRow(imgLoc)<< " next location is y" << getCol(imgLoc)<<std::endl;

            //std::cout << "location  is x " <<imgAry[21][17];
if (accessLocation(tempLoc)!= 1){

    return false;}
            //std::cout << "check x " << getRow(tempLoc)<< " check y" << getCol(tempLoc)<<std::endl;
        }

        return true;
    }

    bool check1(int imgLoc) {


        for (int i = 0; i < structuredPixCount; i++) {
            int tempLoc=imgLoc;

            int rowDiff=(structuredpixels[i]/numColsStructElem)-(origin/numColsStructElem);
            int colDiff=(structuredpixels[i]%numColsStructElem)-(origin%numColsStructElem);
//std::cout << "location  is x " << getRow(imgLoc)+rowDiff<< " next location is y" <<getCol(imgLoc)+colDiff<<std::endl;
            tempLoc=location(getRow(imgLoc)+rowDiff,getCol(imgLoc)+colDiff);
            //std::cout << "location  is x " << getRow(imgLoc)<< " next location is y" << getCol(imgLoc)<<std::endl;

            //std::cout << "location  is x " <<imgAry[21][17];
            if (morphAry[tempLoc / framedArrCols][(tempLoc % framedArrCols)]!= 1){

                return false;}
            //std::cout << "check x " << getRow(tempLoc)<< " check y" << getCol(tempLoc)<<std::endl;
        }

        return true;
    }


    int accessLocation(int loc) {
        //std::cout<<"access location rowss is "<<(loc/framedArrCols)<<"access location cols is "<<(loc%framedArrCols)<<std::endl;
        return imgAry[loc / framedArrCols][(loc % framedArrCols)];


    }
    int  getCol(int loc){
        return loc%framedArrCols;
    }
    int getRow(int loc){return loc/framedArrCols;}

    int accessLocationMor(int loc) {
        //std::cout<<"access location is "<<(loc%framedArrCols)<<std::endl;
        return morphAry[loc / framedArrCols][(loc % framedArrCols)];


    }

    void erosion() {

        //std::cout<<" rowss is "<<(rowFrameSize)<<"cols is "<<(colFrameSize)<<std::endl;
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                if (imgAry[i][j] == 1) {
                    //std::cout<<"access location  ("<<getRow(location(i,j))<<", "<<getCol(location(i,j))<<") number is "<<location(i, j)<<std::endl;
                    if (check(location(i, j))) {
                        morphAry[i][j] = 1;

                    }
                }


            }

        }
    }

    void erosion(int   ** imgtemp) {

        //std::cout<<" rowss is "<<(rowFrameSize)<<"cols is "<<(colFrameSize)<<std::endl;
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                morphAry[i][j] = 0;
                if (imgtemp[i][j] == 1) {
                    //std::cout<<"access location  ("<<getRow(location(i,j))<<", "<<getCol(location(i,j))<<") number is "<<location(i, j)<<std::endl;
                    if (check(location(i, j))) {
                        morphAry[i][j] = 1;

                    }
                }


            }

        }

        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                tempArr[i][j] = morphAry[i][j];



            }

        }
    }

    void dilation() {
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                if (imgAry[i][j] == 1) {
                    //std::cout<<"access location rowss is "<<(i)<<"access location cols is "<<(j)<<std::endl;
                    for (int k = 0; k < structuredPixCount; k++) {
                        int imgLoc=location(i,j);
int tempLoc=imgLoc;
                        int rowDiff=(structuredpixels[k]/numColsStructElem)-(origin/numColsStructElem);
                        int colDiff=(structuredpixels[k]%numColsStructElem)-(origin%numColsStructElem);
//std::cout << "location  is x " << getRow(imgLoc)+rowDiff<< " next location is y" <<getCol(imgLoc)+colDiff<<std::endl;
                        tempLoc=location(getRow(imgLoc)+rowDiff,getCol(imgLoc)+colDiff);


                        morphAry[tempLoc / framedArrCols][(tempLoc % framedArrCols)] = 1;
                    }
                }


            }

        }


    }

    void dilation(int** imgtemp) {
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                if (imgtemp[i][j] == 1) {

                    //std::cout<<"access location rowss is "<<(i)<<"access location cols is "<<(j)<<std::endl;
                    for (int k = 0; k < structuredPixCount; k++) {
                        int imgLoc=location(i,j);
                        int tempLoc=imgLoc;

                        int rowDiff=(structuredpixels[k]/numColsStructElem)-(origin/numColsStructElem);
                        int colDiff=(structuredpixels[k]%numColsStructElem)-(origin%numColsStructElem);
//std::cout << "location  is x " << getRow(imgLoc)+rowDiff<< " next location is y" <<getCol(imgLoc)+colDiff<<std::endl;
                        tempLoc=location(getRow(imgLoc)+rowDiff,getCol(imgLoc)+colDiff);
                        //std::cout << "location  is x " << getRow(imgLoc)<< " next location is y" << getCol(imgLoc)<<std::endl;

                        //std::cout << "location  is x " <<imgAry[21][17];

                        morphAry[tempLoc / framedArrCols][(tempLoc % framedArrCols)] = 1;
                    }
                }


            }

        }
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                tempArr[i][j] = morphAry[i][j];



            }

        }


    }

    void opening() {
        //erosion();
        erosion(imgAry);
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                tempArr[i][j]=morphAry[i][j];
                morphAry[i][j]=0;


            }

        }



        dilation(tempArr);
/*

        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                if (morphAry[i][j] == 1) {
                    //std::cout<<"access location rowss is "<<(i)<<"access location cols is "<<(j)<<std::endl;
                    for (int k = 0; k < structuredPixCount; k++) {
                        int imgLoc=location(i,j);
                        int tempLoc=imgLoc;
                        int rowDiff=(structuredpixels[k]/numColsStructElem)-(origin/numColsStructElem);
                        int colDiff=(structuredpixels[k]%numColsStructElem)-(origin%numColsStructElem);
//std::cout << "location  is x " << getRow(imgLoc)+rowDiff<< " next location is y" <<getCol(imgLoc)+colDiff<<std::endl;
                        tempLoc=location(((imgLoc/framedArrCols)+rowDiff),((imgLoc%framedArrCols)+colDiff));
                        //std::cout << "location  is x " << getRow(imgLoc)<< " next location is y" << getCol(imgLoc)<<std::endl;

                        //std::cout << "location  is x " <<imgAry[21][17];

                        tempArr[tempLoc / framedArrCols][(tempLoc % framedArrCols)] = 1;
                    }
                }


            }

        }


        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
               morphAry[i][j]=tempArr[i][j];



            }

        }
*/

    }

    void opening(int ** imgtemp) {
        //erosion();
        erosion(imgtemp);
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {

                morphAry[i][j]=0;


            }

        }



        dilation(tempArr);


    }
    void closing() {
        //dilation();

        dilation(imgAry);
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {

                morphAry[i][j]=0;


            }

        }



        erosion(tempArr);
        /*

        for (int i = rowFrameSize - 1; i < (rowFrameSize + numRowsImg) - 1; i++) {
            for (int j = colFrameSize - 1; j < (colFrameSize + numColsImg) - 1; j++) {
                if (morphAry[i][j] == 1) {

                    if (check1(location(i, j))) {
                        tempArr[i][j] = 1;

                    }
                }


            }

        }

        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {
                morphAry[i][j]=tempArr[i][j];



            }

        }
        */
    }

    void closing(int** imgtemp) {

        dilation(imgtemp);
        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize; j < (colFrameSize + numColsImg) ; j++) {

                morphAry[i][j]=0;


            }

        }



        erosion(tempArr);

    }


    void mirrorFrame(int *arr[]) {

        for (int i = 0; i < numColsImg; i++) {
            arr[0][i] = arr[1][i];
            arr[numRowsImg - 1][i] = arr[numRowsImg - 2][i];


        }
        for (int i = 0; i < numRowsImg; i++) {
            arr[i][0] = arr[i][1];
            arr[i][numColsImg - 1] = arr[i][numColsImg - 2];


        }


    }


    void printImgOriginal() {


        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize ; j < (colFrameSize + numColsImg) ; j++) {
                std::cout << imgAry[i][j] << " ";


            }
            std::cout << std::endl;
        }


    }
    void printImgFramed() {


        for (int i = 0 ; i < framedArrRows; i++) {
            for (int j = 0 ; j < framedArrCols ; j++) {
                std::cout << imgAry[i][j] << " ";


            }
            std::cout << std::endl;
        }


    }

    void changeStruc(){
        for (int i = 0; i < (numRowsStructElem); i++) {
            for (int j = 0; j < numColsStructElem; j++) {

                 structElemAry[i][j]=0;

            }

        }
        int cn=7;


        structElemAry[2][3]=1;
        structElemAry[2][4]=1;
        structElemAry[3][2]=1;
        structElemAry[3][3]=1;
        structElemAry[3][4]=1;
        structElemAry[4][2]=1;
        structElemAry[4][3]=1;
        structuredpixels[0]=13;
        structuredpixels[1]=14;
        structuredpixels[2]=17;
        structuredpixels[3]=18;
        structuredpixels[4]=19;
        structuredpixels[5]=22;
        structuredpixels[6]=23;

    }





    void printmorph() {


        for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
            for (int j = colFrameSize ; j < (colFrameSize + numColsImg) ; j++) {
                std::cout << morphAry[i][j] << " ";


            }
            std::cout << std::endl;
        }


    }

    void printStruc() {

        for (int i = 0; i < (numRowsStructElem); i++) {
            for (int j = 0; j < numColsStructElem; j++) {

                std::cout << structElemAry[i][j] << " ";

            }
            std::cout << std::endl;
        }
    }

    //void getVals() { std::cout << "number of rows " << numRows << "nunmber of cols " << numCols << std::endl; }


    void loadNeighbors(int i, int j, int *arr[]) {

        int count = 0;
        for (int x = i - 1; x <= i + 1; x++) {
            for (int y = j - 1; y <= j + 1; y++) {
                neighborAry[count] = arr[x][y];
                count++;
            }
        }


    }


    void printAry2File(int *ary[], std::ofstream &output,bool t) {
        int x;
        if (t == true) {
            for (int i = rowFrameSize ; i < (rowFrameSize + numRowsImg) ; i++) {
                for (int j = colFrameSize ; j < (colFrameSize + numColsImg) ; j++) {
                    if(ary[i][j]==1)
                    output << ary[i][j] << " ";
                    else output <<"  ";


                }
                output << std::endl;

            }

        } else{
            for (int i = 0; i < numRowsStructElem; i++) {
                for (int j = 0; j < numColsStructElem; j++) {
                    if(ary[i][j]==1)
                        output << ary[i][j]<< " ";
                    else output <<"  ";


                }
                output << std::endl;

            }
    }
    }

    friend void loadImage(imageProccessing &image, std::ifstream &input);

    friend void loadStruct(imageProccessing &image, std::ifstream &input);
};;

/*
void loadImage(imageProccessing &image, std::ifstream &input) {

    int x;



    for (int i = 1; i < (image.numRows - 1); i++) {
        for (int j = 1; j < image.numCols - 1; j++) {
            input >> x;

            image.mirrorFramedAry[i][j]=x;

        }

    }

    input.close();
}

*/
void loadImage(imageProccessing &image, std::ifstream &input) {
    int x;


    for (int i = image.rowFrameSize; i < (image.rowFrameSize + image.numRowsImg) ; i++) {
        for (int j = image.colFrameSize ; j < (image.colFrameSize + image.numColsImg) ; j++) {
            input >> x;



            //image.mirrorFramedAry[i][j]=x;
            image.imgAry[i][j] = x;



        }

    }

    input.close();
}

void loadStruct(imageProccessing &image, std::ifstream &input) {
    int x;
    int count = 0;
    int tempy[image.numRowsStructElem * image.numColsStructElem];
    for (int i = 0; i < (image.numRowsStructElem); i++) {
        for (int j = 0; j < image.numColsStructElem; j++) {
            input >> x;

            if (x == 1) {
                int loc = (image.numColsStructElem * i) + j;
                tempy[count] = loc;
                count++;


            }

            image.structElemAry[i][j] = x;


        }


    }

    image.structuredpixels = new int[count];
    for (int i = 0; i < count; i++) {
        image.structuredpixels[i] = tempy[i] ;

    }
    image.structuredPixCount = count;

    input.close();
}


int main(int argc, char *argv[]) {

    std::ifstream input1(argv[1]);
    std::ifstream struc(argv[2]);
std::ifstream struc2 (argv[6]);
    std::ofstream outfile1(argv[3]);
    std::ofstream outfile2(argv[4]);
    std::ofstream outfile3(argv[5]);


    int x, y,c,c2;
    int *line1 = new int[4];
    int *strucHead = new int[6];


    for (int i = 0; i < 6; i++) {
        if (i < 4) {
            input1 >> x;
            line1[i] = x;
        }
        struc >> y;

        strucHead[i] = y;


    }


    imageProccessing image1(line1, strucHead);

    loadImage(image1, input1);
    image1.printAry2File(image1.imgAry,outfile1,true);
    loadStruct(image1, struc);
    image1.printAry2File(image1.structElemAry,outfile2,false);
int r=10;
int r2=1;


    while (r!=0){

        std::cout<<"for dilation enter 1"<<std::endl;
        std::cout<<"for erosion enter 2"<<std::endl;
        std::cout<<"for opening enter 3"<<std::endl;
        std::cout<<"for closing enter 4"<<std::endl;
        std::cout<<"TO EXIT ENTER 0"<<std::endl;
        std::cout << std::endl;
        std::cin>>c;
        r=c;
        if(c==0) break;
        std::cout<< "please enter which  image/n press 1 for imgary/n press 2 for morphAry";
        std::cout << std::endl;
        std:: cin>>c2;
        std::cout << std::endl;


        r2=c2;


        if(c==1){
            if(c2==1){
                image1.dilation(image1.imgAry);
                image1.printmorph();
            }
            else if(c2==2){

                image1.dilation(image1.tempArr);

                image1.printmorph();

            }
            /*
            image1.dilation();
            image1.printmorph();
        image1.printAry2File(image1.morphAry,outfile3,true);
        */}
        else if(c==2){

            if(c2==1){
                image1.erosion(image1.imgAry);
                image1.printmorph();
        }
            else if(c2==2){

                image1.erosion(image1.tempArr);
                image1.printmorph();
            }
        /*
            image1.erosion();
            image1.printmorph();
            image1.printAry2File(image1.morphAry,outfile3,true);
        */}
        else if(c==3){
            if(c2==1){
                image1.opening(image1.imgAry);
                image1.printmorph();
            }
            else if(c2==2){
                image1.opening(image1.tempArr);
                image1.printmorph();
            }
            /*
            image1.opening();
            image1.printmorph();
            image1.printAry2File(image1.morphAry,outfile3,true);
            */

        }
        else if(c==4){
            if(c2==1){
                image1.closing(image1.imgAry);
                image1.printmorph();
            }
            else if(c2==2){
                image1.opening(image1.tempArr);
                image1.printmorph();
            }
            /*
            image1.closing();
            image1.printmorph();
            image1.printAry2File(image1.morphAry,outfile3,true);*/
        }



    }

image1.changeStruc();


image1.dilation(image1.tempArr);

    std::cout << std::endl;

    std::cout << std::endl;

    image1.printmorph();

    image1.printAry2File(image1.morphAry,outfile3,true);
    delete[] line1;
    delete[]strucHead;

    return 0;
}