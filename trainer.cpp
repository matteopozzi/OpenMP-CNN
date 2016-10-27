#include <vector>
#include <iostream>

public class layerTrainer{

    private:
      int height = 0;
      int width = 0;
      vector<vector<double>> layerWeights;
      vector<vector<double>> layerBiases;
      double learningRate;
      double weightDecay;
      int batchSize;

    public:
      layerTrainer(vector<vector<double>> layerWeights, vector<vector<double>> layerBiases, double learningRate, double weightDecay, int batchSize){
          this.learningRate = learningRate;
          this.weightDecay = weightDecay;
          this.batchSize = batchSize;
          this.layerBiases =layerBiases;
          this.layerWeights = layerWeights;
          this.height = layerWeights.size();
          this.width = layerWeights[0].size();
      }

      using namespace std;

      vector<vector<int>> upsample(vector<vector<int>> &backPropagatedError, vector<vector<int>> &derivativeOfAggregation){
          int height1 = backPropagatedError.size();
          int width1 = backPropagatedError[0].size();
          int height2 = derivativeOfAggregation.size();
          int width2 = derivativeOfAggregation[0].size();
          int row, column;
          vector<vector<int>> upsampleValuesMatrix(height1 * height2, vector<int>(width1 * width2));
          for (int i = 0; i < height1; i++){
              for (int j = 0; j < width1; j++){
                  for (int k = 0; k < height2; k++){
                      for (int z = 0; z < width2; z++){
                          //cout << i << ", " << j << ", " << k << ", " << z << endl;
                          //cout << derivativeOfAggregation[k][z] << endl;
                          row = i * height2 + k;
                          column = j * width2 + z;
                          upsampleValuesMatrix[row][column] = backPropagatedError[i][j] * derivativeOfAggregation[k][z];
                      }
                  }
                  //cout << backPropagatedError[i][j] << endl;
              }
          }
          return upsampleValuesMatrix;
    }

    void layerUpdater(){
        vector<vector<double>> deltaW(height, vector<double>(width));
        vector<vector<double>> deltaB(height, vector<double>(width));
        for(int b=0;b<batchSize;b++){
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    deltaW[i][j] += backPropagation();
                    deltaB[i][j] += backPropagation();
                }
            }
        }
        for(int b=0;b<batchSize;b++){
            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    layerWeights[i][j]=layerWeights[i][j]-(learningRate*(((1/batchSize)*deltaW)+weightDecay*layerWeights[i][j]));
                    layerBiases[i][j]=layerBiases[i][j]-(learningRate*((1/batchSize)*deltaB));
                }
            }
        }
    }

    double backPropagation(){
        
    }
    

    int main(){
        vector<vector<int>> m1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        vector<vector<int>> m2{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
        int i, j;
        int count = 0;
        vector<vector<int>> up = upsample(m1, m2);
        for (i = 0; i < up.size(); i++)
        {
            for (j = 0; j < up.size(); j++)
            {
                count += 1;
                cout << up[i][j] << " ";
                if (count == up.size())
                {
                    count = 0;
                    cout << endl;
                }
            }
        }
    }
}