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
\[
\sigma(z) = \frac{1}{1 + e^{-z}}
\]
where \( z = w \cdot x + b \), with \( w \) as weights, \( x \) as input, and \( b \) as the bias term.

#### Binary Cross-Entropy Loss
For Logistic Regression, the model optimizes the binary cross-entropy loss:
\[
L(y, \hat{y}) = - \frac{1}{N} \sum_{i=1}^N \left[ y_i \log(\hat{y}_i) + (1 - y_i) \log(1 - \hat{y}_i) \right]
\]
where \( y \) is the true label, \( \hat{y} \) is the predicted probability, and \( N \) is the number of samples.

### 2. Linear Discriminant Analysis (LDA)

LDA aims to maximize separability between classes by projecting data onto a lower-dimensional space where class separation is maximized.

#### Discriminant Function
The LDA model calculates a discriminant score for each class:
\[
d_k(x) = x^T \Sigma^{-1} \mu_k - \frac{1}{2} \mu_k^T \Sigma^{-1} \mu_k + \log(P_k)
\]
where \( x \) is the input feature vector, \( \Sigma \) is the covariance matrix, \( \mu_k \) is the mean vector for class \( k \), and \( P_k \) is the prior probability of class \( k \).

### 3. K-Nearest Neighbors (KNN)

K-Nearest Neighbors classifies data points based on the majority class of their \( k \) nearest neighbors.

#### Euclidean Distance
The Euclidean distance between points helps find nearest neighbors:
\[
d(x_i, x_j) = \sqrt{\sum_{k=1}^{n} (x_{ik} - x_{jk})^2}
\]
where \( x_i \) and \( x_j \) are two data points, and \( n \) is the number of features.

### 4. Decision Tree Classifier (CART)

The Decision Tree Classifier splits data based on features that maximize class separation.

#### Gini Impurity
The model uses Gini impurity to measure the quality of splits:
\[
Gini = 1 - \sum_{i=1}^C p_i^2
\]
where \( p_i \) is the probability of selecting a sample with class \( i \) in a subset, and \( C \) is the number of classes.

### 5. Naive Bayes (NB)

Naive Bayes applies Bayes' theorem, assuming feature independence.

#### Bayes' Theorem
The conditional probability of class \( C_k \) given input \( x \) is:
\[
P(C_k | x) = \frac{P(x | C_k) \cdot P(C_k)}{P(x)}
\]

### 6. Support Vector Machine (SVM)

SVM identifies the hyperplane that maximizes margin between classes.

#### Margin Optimization
To maximize the margin:
\[
\min \frac{1}{2} ||w||^2 \quad \text{subject to } y_i (w \cdot x_i + b) \geq 1
\]

#### Hinge Loss Function
SVM minimizes the hinge loss:
\[
L(y, \hat{y}) = \max(0, 1 - y \cdot \hat{y})
\]

---

## Cross-Validation with StratifiedKFold

To ensure balanced training, we use **StratifiedKFold cross-validation**. This approach maintains class proportions within each fold, providing a more reliable evaluation for imbalanced datasets.

### Cross-Validation Formula

Let \( k \) be the number of folds, and \( D \) be the dataset. Cross-validation involves:

1. Splitting \( D \) into \( k \) equally-sized folds \( D_1, D_2, \ldots, D_k \).
2. For each \( i \)-th fold:
   - Use \( D_i \) as the validation set and \( D - D_i \) as the training set.
   - Calculate the accuracy \( A_i \) on \( D_i \).
3. The final accuracy is the average over all folds:
\[
\text{Accuracy} = \frac{1}{k} \sum_{i=1}^k A_i
\]

Cross-validation provides a more generalized evaluation by leveraging the entire dataset for both training and validation.

---

## Model Evaluation

We evaluate each model with **cross-validation** and **accuracy** as the primary metric. Results are visualized with a bar chart, comparing each algorithm’s performance.

### Code Files

- **[EvaluatingVariousMLModelforEnergyMeter.ipynb](./EvaluatingVariousMLModelforEnergyMeter.ipynb)**: Code for loading, visualizing, and evaluating models.
- **[Training&TestingMLAlgorithmForEnergyMeter.ipynb](./Training&TestingMLAlgorithmForEnergyMeter.ipynb)**: Training and evaluating the final model.
- **[finalized_model.pkl](./finalized_model.pkl)**: The saved final model.

---

## Summary

In this session, we covered essential ML concepts and demonstrated the application of supervised learning models to IoT data. By training ML models on labeled energy meter data, we enable predictive capabilities that enhance IoT systems' intelligence, improving efficiency and automation in real-world applications.
