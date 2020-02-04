import sys
import copy

def parChecker(symbolString):
    s = [] #Stack
    balanced = True
    index = 0
    while index < len(symbolString) and balanced:
        symbol = symbolString[index]
        if symbol == "(":
            s.append(symbol)
        elif symbol == ")":
            try:
                s.pop()
            except IndexError:
                balanced = False
        index = index + 1

    if balanced and len(s) == 0:
        return True
    else:
        return False

# Nota: Los paréntesis deben estar balanceados en s
def get_couple(s, bracket_pos):
    star_index = bracket_pos+1
    end_index = len(s)
    while 0==0:
        couple = s.rfind(')', star_index, end_index)
        if(parChecker(s[star_index:couple])):
            break
        end_index = couple
    return couple

def delete_parents(s):
    s_aux = copy.copy(s)
    
    while 0==0:
        try:
            first_p = s_aux.index('(')
        except ValueError:
            break
        last_p = get_couple(s_aux, first_p)
        s_aux = s_aux[:first_p] + (last_p-first_p+1)*" " + s_aux[last_p+1:]
    return s_aux

def get_pos_lower_priority(s):
    s_aux = delete_parents(s)

    if ('+' in s_aux or '-' in s_aux):
        if (s_aux.rfind('+') >= s_aux.rfind('-')):
            return s_aux.rfind('+')
        else:
            return s_aux.rfind('-')

    if ('*' in s_aux or '/' in s_aux):
        if (s_aux.rfind('*') >= s_aux.rfind('/')):
            return s_aux.rfind('*')
        else:
            return s_aux.rfind('/')

def delete_first_parents(s):
    while 0==0:
        if (s[0] == '(' and s[-1] == ')' and parChecker(s[1:-1])):
            s = s[1:-1]
        else:
            break
    return s    

def pintar(s):
    s = s.replace(" ", "") #Elimina blancos
    s = delete_first_parents(s)
    try:
        int(s)
        print(s, end="")
        return
    except ValueError:
        pass
    
    pos_operador = get_pos_lower_priority(s)
    f_operando = s[:pos_operador]
    l_operando = s[pos_operador+1:]
    print('(' + s[pos_operador], end=" ")
    pintar(f_operando)
    print(' ', end="")
    pintar(l_operando)
    print(")", end="")

    
n = int(sys.stdin.readline())
for caso in range(n):
    cadena = sys.stdin.readline()[:-1]
    pintar(cadena)
    print()
    
