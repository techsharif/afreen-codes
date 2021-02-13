text = input("Text: ")

letters = 0
words = 1
sentences = 0

ln = len(text)

for i in range(ln):
    if text[i].isalpha():
        letters = letters + 1

    if text[i] == ' ':
        words = words + 1

    if text[i] == '.' or text[i] == '?' or text[i] == '!':
        sentences = sentences + 1

L = letters * 100 / words
S = sentences * 100 / words

grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print("Grade ", grade)

