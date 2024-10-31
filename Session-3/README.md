# Session-3: Introduction to Machine Learning and Sensor Data Modeling

In this session, we will explore how machine learning (ML) can be applied to IoT data, specifically from an energy meter, to create predictive models that add intelligence to IoT systems. This guide introduces ML, the dataset we are using, and the algorithms applied in this session, along with essential equations and explanations.

## Objectives

1. Understand machine learning and its types, with a focus on supervised learning.
2. Explore and visualize a real-world dataset from an energy meter.
3. Apply and evaluate various machine learning algorithms to model sensor data.

---

## Types of Machine Learning

There are three main types of machine learning, each suited to different kinds of tasks:

1. **Supervised Learning**: The model learns from a labeled dataset, meaning each input has a known output. This is used for tasks like classification and regression, where the aim is to predict outcomes based on past data. Our dataset in this session is supervised, as it includes features (Voltage, Current, Power) and a **Class** label.
  
2. **Unsupervised Learning**: The model identifies patterns or structures in data without labeled outputs. Examples include clustering and dimensionality reduction, where insights are derived without predefined categories.
  
3. **Reinforcement Learning**: The model learns through trial and error, receiving feedback as rewards or penalties based on actions. This is commonly applied in areas like robotics, where an agent learns optimal behaviors by interacting with an environment.

---

## Why Use Machine Learning in IoT?

Machine learning in IoT helps:
- **Detect anomalies**: Identify unusual data patterns, which may indicate device malfunctions.
- **Predict future events**: Such as forecasting power consumption.
- **Automate responses**: For example, taking action based on predictive outcomes.
- **Improve decision-making**: Enhance the efficiency of smart systems like cities or industrial setups.

### Supervised Learning and Our Dataset

Our dataset, **Energy Meter.csv**, is designed for a supervised learning task. Each row represents a measurement of voltage, current, power, and a **Class** label that categorizes the state of energy usage. By training models on this labeled data, we can build classifiers that predict the class of new measurements based on input features.

---

## Dataset Overview

The dataset includes these attributes:
- **Voltage**: Voltage in volts.
- **Current**: Current in amperes.
- **Power**: Power in watts.
- **Class**: The label indicating the operating state or type of energy usage.

### Dataset File
- **[Energy Meter.csv](./Energy%20Meter.csv)**

---

## Visualization of Data

Data visualizations provide insights into the feature distributions and relationships:
- **Bar Plot**: Shows the distribution of each feature across different measurements.
- **Histogram Plot**: Displays frequency distribution.
- **Scatter Matrix Plot**: Shows pairwise relationships between features to identify patterns.

The code for data visualization can be found in:
- **[EvaluatingVariousMLModelforEnergyMeter.ipynb](./EvaluatingVariousMLModelforEnergyMeter.ipynb)** (Jupyter Notebook)
- **[EvaluatingVariousMLModelforEnergyMeter.py](./EvaluatingVariousMLModelforEnergyMeter.py)** (Python script)

---

## Machine Learning Algorithms and Key Equations

Here, we describe the ML algorithms applied in this session, including equations for each model’s loss function and other essential calculations.

### 1. Logistic Regression (LR)

Logistic Regression is a classification algorithm that predicts the probability that an input belongs to a particular class. It uses the **Sigmoid function** to map predicted values to probabilities.

#### Sigmoid Function
![Sigmoid Function](https://latex.codecogs.com/png.image?\dpi{120}\color{White}\sigma(z)&space;=&space;\frac{1}{1&plus;e^{-z}})

This is where `z = w.x + b`, with `w` as weights, `x` as input, and `b` as the bias term.

#### Binary Cross-Entropy Loss
For Logistic Regression, the model optimizes the binary cross-entropy loss:

![Binary Cross-Entropy](https://latex.codecogs.com/png.image?\dpi{120}\color{White}L(y,&space;\hat{y})&space;=&space;-&space;\frac{1}{N}&space;\sum_{i=1}^N&space;\left[&space;y_i&space;\log(\hat{y}_i)&space;&plus;&space;(1&space;-&space;y_i)&space;\log(1&space;-&space;\hat{y}_i)&space;\right])

### 2. Linear Discriminant Analysis (LDA)

LDA aims to maximize separability between classes by projecting data onto a lower-dimensional space where class separation is maximized.

#### Discriminant Function
![Discriminant Function](https://latex.codecogs.com/png.image?\dpi{120}\color{White}d_k(x)&space;=&space;x^T&space;\Sigma^{-1}&space;\mu_k&space;-&space;\frac{1}{2}&space;\mu_k^T&space;\Sigma^{-1}&space;\mu_k&space;&plus;&space;\log(P_k))

### 3. K-Nearest Neighbors (KNN)

K-Nearest Neighbors classifies data points based on the majority class of their \( k \) nearest neighbors.

#### Euclidean Distance
![Euclidean Distance](https://latex.codecogs.com/png.image?\dpi{120}\color{White}d(x_i,&space;x_j)&space;=&space;\sqrt{\sum_{k=1}^{n}&space;(x_{ik}&space;-&space;x_{jk})^2})

### 4. Decision Tree Classifier (CART)

The Decision Tree Classifier splits data based on features that maximize class separation.

#### Gini Impurity
![Gini Impurity](https://latex.codecogs.com/png.image?\dpi{120}\color{White}Gini&space;=&space;1&space;-&space;\sum_{i=1}^C&space;p_i^2)

### 5. Naive Bayes (NB)

Naive Bayes applies Bayes' theorem, assuming feature independence.

#### Bayes' Theorem
![Bayes Theorem](https://latex.codecogs.com/png.image?\dpi{120}\color{White}P(C_k&space;|&space;x)&space;=&space;\frac{P(x&space;|&space;C_k)&space;\cdot&space;P(C_k)}{P(x)})

### 6. Support Vector Machine (SVM)

SVM identifies the hyperplane that maximizes margin between classes.

#### Margin Optimization
![Margin Optimization](https://latex.codecogs.com/png.image?\dpi{120}\color{White}\min&space;\frac{1}{2}&space;||w||^2&space;\quad&space;\text{subject&space;to&space;}&space;y_i&space;(w&space;\cdot&space;x_i&space;&plus;&space;b)&space;\geq&space;1)

#### Hinge Loss Function
![Hinge Loss](https://latex.codecogs.com/png.image?\dpi{120}\color{White}L(y,&space;\hat{y})&space;=&space;\max(0,&space;1&space;-&space;y&space;\cdot&space;\hat{y}))

---

## Cross-Validation with StratifiedKFold

To ensure balanced training, we use **StratifiedKFold cross-validation**. This approach maintains class proportions within each fold, providing a more reliable evaluation for imbalanced datasets.

### Cross-Validation Formula

Let `k` be the number of folds, and `D` be the dataset. Cross-validation involves:

1. Splitting `D` into `k` equally-sized folds ![D_1](https://latex.codecogs.com/png.image?\dpi{120}\color{White}D_{1}) and ![D_2](https://latex.codecogs.com/png.image?\dpi{120}\color{White}D_{2}), ..., ![D_k](https://latex.codecogs.com/png.image?\dpi{120}\color{White}D_{k}).
2. For each ![i](https://latex.codecogs.com/png.image?\dpi{120}\color{White}i)-th fold:
   - Use ![D_i](https://latex.codecogs.com/png.image?\dpi{120}\color{White}D_{i}) as the validation set and ![D-D_i](https://latex.codecogs.com/png.image?\dpi{120}\color{White}D-D_{i}) as the training set.
   - Calculate the accuracy ![A_i](https://latex.codecogs.com/png.image?\dpi{120}\color{White}A_{i}) on ![D_i](https://latex.codecogs.com/png.image?\dpi{120}\color{White}D_{i}).
3. The final accuracy is the average over all folds:
   
   ![Cross-Validation Accuracy](https://latex.codecogs.com/png.image?\dpi{120}\color{White}\text{Accuracy}&space;=&space;\frac{1}{k}&space;\sum_{i=1}^k&space;A_i)

Cross-validation provides a more generalized evaluation by leveraging the entire dataset for both training and validation.

---

## Model Evaluation

We evaluate each model with **cross-validation** and **accuracy** as the primary metric. Results are visualized with a bar chart, comparing each algorithm’s performance.

### Code Files

- **[EvaluatingVariousMLModelforEnergyMeter.ipynb](./EvaluatingVariousMLModelforEnergyMeter.ipynb)**
- **[EvaluatingVariousMLModelforEnergyMeter.py](./EvaluatingVariousMLModelforEnergyMeter.py)**

---

This detailed README provides foundational knowledge and hands-on practice with ML algorithms, setting the stage for further exploration in the field of IoT-enhanced intelligence.
