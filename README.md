# Option-Pricer-Cpp
Option Pricing Project using 3 pricing models with C++
---

# 🎨 **C++ OPTION PRICING PROJECT**

### *Black–Scholes • CRR • Monte-Carlo • Path-Dependent Options*

---

## 📝 **Overview**

This repository contains a full-featured **C++ option pricing framework** developed for the *C++ for Finance – 2023* project.
It implements the complete option hierarchy and the main numerical pricing engines used in quantitative finance.

This README is written in a polished, stylistic format:

* Serif-style section headers
* Sans-serif-style body text
* Small-caps emphasis
* Unicode symbols for elegance

---

# 🧭 **Table of Contents**

1. [Project Architecture](#project-architecture)
2. [Option Class Hierarchy](#option-class-hierarchy)
3. [Pricing Engines](#pricing-engines)
4. [Core Data Structures](#core-data-structures)
5. [Random Number Generator](#random-number-generator)
6. [Compilation & Usage](#compilation--usage)
7. [Project Constraints](#project-constraints)

---

# 🏗️ **Project Architecture**

```
src/
│
├── options/
│     ├── Option.hpp / Option.cpp
│     ├── VanillaOption.hpp / .cpp
│     ├── DigitalOption.hpp / .cpp
│     ├── AsianOption.hpp / .cpp
│     ├── (Call, Put, DigitalCall, ..., AsianPut)
│
├── pricers/
│     ├── BlackScholesPricer.hpp / .cpp
│     ├── BlackScholesMCPricer.hpp / .cpp
│     ├── CRRPricer.hpp / .cpp
│
├── utils/
│     ├── BinaryTree.hpp
│     ├── MT.hpp   (singleton RNG)
│
└── main.cpp
```

The architecture follows clean **object-oriented design**, with clear separation between:

* *Products* (options)
* *Models* (pricers)
* *Data structures* (trees, RNG)

---

# 🪙 **Option Class Hierarchy**

## **1. Base Class — `Option`**

**Abstract** class providing:

* `double payoff(double)`
* `double payoffPath(std::vector<double>)`
* `double getExpiry()`
* `bool isAsianOption()`
* `bool isAmericanOption()`

Path-dependent payoff routes to:

* Standard payoff for vanilla options
* Averaging logic for Asian options

---

## **2. European Vanilla Options**

Small-caps *call* and *put* payoffs:

```
Call:  max(S − K, 0)
Put:   max(K − S, 0)
```

Classes:

* `VanillaOption` (abstract)
* `CallOption`
* `PutOption`

---

## **3. Digital Options**

Binary payouts:

```
Digital Call:  1(S ≥ K)
Digital Put:   1(S ≤ K)
```

Classes:

* `DigitalOption` (abstract)
* `DigitalCallOption`
* `DigitalPutOption`

---

## **4. Asian Options (Path-Dependent)**

Arithmetic average payoff:

```
AsianCall: max( avg(S₁…Sₘ) − K , 0 )
AsianPut:  max( K − avg(S₁…Sₘ) , 0 )
```

Classes:

* `AsianOption`
* `AsianCallOption`
* `AsianPutOption`

Asian options cannot be priced by CRR → detected and rejected via exception.

---

# 💸 **Pricing Engines**

---

## 🎯 **Black–Scholes (Closed-Form)**

Class: **`BlackScholesPricer`**

Supports:

* Vanilla Call/Put
* Digital Call/Put

Implements:

* Price via `operator()`
* Analytical *Delta*
* Uses `std::erfc` for the normal CDF

---

## 🌳 **Cox–Ross–Rubinstein Binomial Model**

Class: **`CRRPricer`**

Features:

* Handles European *and American* options
* Arbitrage check: `D < R < U`
* Backward induction
* Risk-neutral probability
* Optional: **closed-form binomial formula**

Also stores *early exercise policy* in:

* `BinaryTree<bool>`

### **Black–Scholes limit**

A special constructor computes:

* `U`, `D`, `R` from `(r, σ, T, N)`
  for convergence to the continuous BS model.

---

## 🎲 **Monte Carlo Black–Scholes Simulation**

Class: **`BlackScholesMCPricer`**

Capabilities:

* Simulates sample paths using geometric Brownian motion
* Works for Vanilla, Digital, and *Asian* options
* Updates estimator incrementally
* Computes **95% confidence interval**
* Tracks total number of generated paths

Relies on:

* `MT::rand_norm()` for Gaussian increments

---

# 🧱 **Core Data Structures**

---

## 🗂️ **Binary Tree — `BinaryTree<T>`**

Template lattice used for CRR pricing:

* Adjustable depth
* `setNode(n, i, value)`
* `getNode(n, i)`
* Pretty-print `display()`
* Supports types: `double`, `bool`, etc.

Used for:

* Value lattices
* Early-exercise indicator lattices

---

# 🔢 **Random Number Generator**

---

## 🔧 Singleton RNG — `MT`

A single global `std::mt19937` instance.

Methods:

* `rand_unif()` → Uniform(0,1)
* `rand_norm()` → Normal(0,1)

Ensures reproducible + consistent MC behavior across the app.

---

