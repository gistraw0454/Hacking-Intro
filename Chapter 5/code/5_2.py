# ���� 5-2 ) �Է� �������� �Ϻθ� ������ �����ϴ� ���̽� �Լ��� 50������ A�� �ش� �Լ��� �־��� �� ����� ���� ��� ���
import random

def mutate(data, n=20):
    tmp = [c for c in data]
    for _ in range(n):
        tmp[random.randint(0, len(tmp) - 1)] = chr(random.randint(0, 255))
    return ''.join(tmp)

print(repr(mutate('A' * 50)))
print(repr(mutate('A' * 50)))
print(repr(mutate('A' * 50)))
print(repr(mutate('A' * 50)))
