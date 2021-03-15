
    sort(priceOfJeans.begin(), priceOfJeans.end());
    sort(priceOfShoes.begin(), priceOfShoes.end());
    sort(priceOfSkirts.begin(), priceOfSkirts.end());
    sort(priceOfTops.begin(), priceOfTops.end());
    
    vector<int> SumArr(priceOfJeans.size() * priceOfShoes.size(),0);
    unsigned int index =0;
    for(unsigned int i=0;i<priceOfJeans.size();i++){
        if(priceOfJeans[i] >= dollars){
            break;
        }
        for(unsigned int j=0;j<priceOfShoes.size();j++){
            if(priceOfShoes[j] >= dollars ){
                break;
            }
            
            if(priceOfShoes[j] + priceOfJeans[i] <= dollars){
                SumArr[index++] = priceOfJeans[i] + priceOfShoes[j];
            }
            else{
                break;
            }
        }
    }
    
    int abcIndex =0;
    vector<int> abcSum(index * priceOfSkirts.size(), 0);
    
    for(unsigned int i=0;i<index;i++){
        if(SumArr[i] == 0){
            break;
        }
        for(unsigned int j=0;j<priceOfSkirts.size();j++){
            
            if(priceOfSkirts[j] >= dollars){
                break;
            }
            if(SumArr[i] + priceOfSkirts[j] <= dollars){
                abcSum[abcIndex++] = SumArr[i] + priceOfSkirts[j];
            }
            else{
                break;
            }
        }
    }
    
    int result =0;
    
    for(unsigned int i=0;i<(int)abcIndex;i++){
        if(abcSum[i] == 0){
            break;
        }
        for(unsigned int j=0;j<priceOfTops.size();j++){
            if(abcSum[i] + priceOfTops[j] <= dollars){
                result++;
            }else{
                break;
            }
        }
    }
    
    return result;