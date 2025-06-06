// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int PrOSym(char symbol) {
  switch (symbol) {
      case '(': return 0;
      case ')': return 1;
      case '+':
      case '-': return 2;
      case '*':
      case '/': return 3;
      default : return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  std::string postfix = "";
  TStack<char, 100> transferStack;

  for (int i = 0; i < inf.length(); ++i) {
      char curr = inf[i];
      if (isdigit(curr)) {
          std::string num;
          while (i < inf.length() && isdigit(inf[i])) {
              num += inf[i];
              i++;
          }
          i--;
          postfix += num + " ";
      } else if (curr == '(') {
          transferStack.push(curr);
      } else if (curr == ')') {
          while (!transferStack.isEmpty() && transferStack.get() != '(') {
              postfix += transferStack.pop();
              postfix += " ";
          }
          if (!transferStack.isEmpty() && transferStack.get() == '(') {
              transferStack.pop();
          }
      } else if (curr == '+' || curr == '-' || curr == '*' || curr == '/') {
          while (!transferStack.isEmpty() 
            && PrOSym(curr) <= PrOSym(transferStack.get())) {
              postfix += transferStack.pop();
              postfix += " ";
          }
          transferStack.push(curr);
      } else if (curr == ' ') {
          continue;
      }
  }
  while (!transferStack.isEmpty()) {
      postfix += transferStack.pop();
      postfix += " ";
  }
  if (!postfix.empty() && postfix.back() == ' ') {
     postfix.pop_back();
  }
    return postfix;
}

int eval(const std::string& post) {
  std::string currentNumber;
  TStack<int, 100> NumStack;
  for (int i = 0; i < post.length(); ++i) {
      char currSym = post[i];
      if (isdigit(currSym)) {
          currentNumber += currSym;
      } else if (currSym == ' ') {
          if (!currentNumber.empty()) {
              NumStack.push(stoi(currentNumber));
              currentNumber.clear();
          }
      } else if (currSym == '+' || currSym == '-'
        || currSym == '*' || currSym == '/') {
          if (NumStack.isEmpty()) {
              return 0;
          }
          int op2 = NumStack.pop();
          if (NumStack.isEmpty()) {
              return 0;
          }
          int op1 = NumStack.pop();
          int res;
          switch (currSym) {
              case '+':
                  res = op1 + op2;
                  break;
              case '-':
                  res = op1 - op2;
                  break;
              case '*':
                  res = op1 * op2;
                  break;
              case '/':
                  if (op2 == 0) {
                       return 0;
                  }
                  res = op1 / op2;
                  break;
              default:
                  return 0;
          }
          NumStack.push(res);
      }
  }
  if (NumStack.isEmpty()) {
      return 0;
  }
  return NumStack.pop();
}
