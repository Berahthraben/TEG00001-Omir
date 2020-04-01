#!/usr/bin/env python
# -*- coding: utf-8 -*-
import PySimpleGUI as sg
from math import log10 as log, ceil as ceil
import os
import copy

sg.theme('Dark Blue 3')
matriz_main = []
adjacencia = False
direcionado = False
headings = ['1', '2']
header = [[sg.Text(' ' + h, size=(2, 1)) for h in headings]]
input_rows = [[sg.Input(size=(3, 1), pad=(1, 1)) for col in range(2)] for row in range(2)]
layoutMain = [[sg.Text('Importar grafo de um arquivo')],
              [sg.Input(key='buscarArquivo', enable_events=True), sg.FileBrowse("Buscar", target='buscarArquivo')],
              [sg.Text('Direcionado:', font='Arial 14', pad=(1, 1)),
               sg.Text('N/D', key='isDirecionado', font='Arial 14', pad=(1, 1)),
               sg.Text('Carregado:', font='Arial 14', pad=(1, 1)),
               sg.Text('Não', key='isCarregado', font='Arial 14', pad=(1, 1))],
              [sg.Button("Grau de vértice", key='grauNo'),
               sg.Button("Testar desconexão", key='testarDesconexo')],
              [sg.Button("Matriz do complemento", key='complemento'),
               sg.Button("Ver/Editar matriz adjacência", key='abrirEditar')],
              [sg.Button("Testar Circuito Euleriano (Fleury)", key='fleury')]]

"""

   ## PROCESSAMENTO DO MENU PRINCIPAL

"""


def main(args):
    global direcionado
    global adjacencia
    global matriz_main
    window_main = sg.Window('Programa de grafos TEG0001 - Nicolas Ribeiro e Maísa',
                            layoutMain,
                            font='Arial 16',
                            element_justification="center",
                            auto_size_buttons=True,
                            auto_size_text=True)
    while True:
        event, values = window_main.read()
        if event == 'grauNo':
            if not matriz_main:
                sg.Popup("Primeiro carregue um grafo no registro!")
            else:
                calcular_grau_no(True, 0)
        elif event == 'abrirEditar':
            if not matriz_main:
                sg.Popup("Primeiro carregue um grafo no registro!")
            else:
                abrir_editar()
        elif event == 'buscarArquivo':
            sucesso = carregar_arquivo(values['buscarArquivo'])
            if sucesso == 1:
                direcionado = testar_direcionado()
                if direcionado:
                    window_main['isDirecionado'].update("Sim")
                else:
                    window_main['isDirecionado'].update("Não")
                window_main['isCarregado'].update("Sim")
        elif event == 'complemento':
            if not matriz_main:
                sg.Popup("Primeiro carregue um grafo no registro!")
            else:
                abrir_complemento()
        elif event == 'testarDesconexo':
            if not matriz_main:
                sg.Popup("Primeiro carregue um grafo no registro!")
            else:
                desconexo = testar_conexo(matriz_main)
                if desconexo:
                    sg.Popup("Grafo é desconexo!")
                else:
                    sg.Popup("Grafo não é desconexo!")
        elif event == 'fleury':
            if not matriz_main:
                sg.Popup("Primeiro carregue um grafo no registro!")
            else:
                processar_fleury()
        elif event is None:
            break


"""

   ## ALGORITMO DE FLEURY

"""


def processar_fleury():
    global matriz_main
    matriz_teste = copy.deepcopy(matriz_main)
    numero_impares = 0
    vertice_impar = 0
    if testar_conexo(matriz_main):
        sg.Popup("Não existe caminho Euleriano. Grafo é naturalmente desconexo.")
    for i in range(len(matriz_main)):
        grau = calcular_grau_no(False, i)
        if grau % 2 != 0:
            numero_impares = numero_impares + 1
            vertice_impar = i
            if numero_impares > 2:
                sg.Popup("Não existe caminho Euleriano. Mais de dois vértices com grau ímpar.")
                return
    if numero_impares == 1:
        sg.Popup("Não existe caminho Euleriano. Apenas um vértice tem grau ímpar.")
        return
    elif numero_impares == 2:
        pontes = testar_pontes()
        print(pontes)
        i = vertice_impar  # Começar do vertice na var vertice_impar
        j = 0
        aux = [vertice_impar]
        while True:
            a = matriz_teste[i][j]
            if a > 0:
                if [i, j] in pontes:
                    for k in range(len(matriz_teste[i])):  # Testa pra ver se existe outras opções
                        if k == j:
                            continue
                        if matriz_teste[i][k] > 0:
                            matriz_teste[i][k] = 0  # Elimina a aresta inicial
                            matriz_teste[k][i] = 0  # Elimina a aresta final
                            if k not in aux:
                                aux.append(k)
                            i, j = k, 0
                        if k == len(matriz_teste)-1:  # Pular pela ponte
                            matriz_teste[i][j] = 0
                            matriz_teste[j][i] = 0
                            if j not in aux:
                                aux.append(j)
                            i, j = j, 0
                else:
                    matriz_teste[i][j] = 0
                    matriz_teste[j][i] = 0
                    aux.append(j)
                    i, j = j, i
            elif a == 0 and j == len(matriz_teste) - 1:
                break
            else:
                j = j + 1
        if len(aux) < len(matriz_teste):
            print(aux)
            sg.Popup("Não existe caminho euleriano")
        else:
            print(aux)
            sg.Popup("Existe caminho euleriano")


"""

    ## TESTA QUAIS VÉRTICES SÃO PONTES

"""


def testar_pontes():
    global matriz_main
    matriz_teste = copy.deepcopy(matriz_main)
    pontes = []
    for i in range(len(matriz_teste)):
        for j in range(len(matriz_teste[i])):
            if matriz_teste[i][j] > 0:
                matriz_teste[i][j] = 0
                matriz_teste[j][i] = 0
                desconexo = testar_conexo(matriz_teste)
                if desconexo:
                    pontes.append([i, j])
                matriz_teste[i][j] = 1
                matriz_teste[j][i] = 1
    return pontes


"""

   ## ABRE DIÁLOGO DO COMPLEMENTO

"""


def abrir_complemento():
    layout_complemento = gerar_layout('complemento')
    window_complemento = sg.Window('Visualizar matriz complemento',
                                   layout_complemento,
                                   font='Arial 16',
                                   element_justification="center",
                                   auto_size_buttons=True,
                                   no_titlebar = True,
                                   grab_anywhere=True,
                                   auto_size_text=True)
    event2, values2 = window_complemento.read(close=True)
    if event2 is None or event2 == 'fecharCompl':
        window_complemento.close()


"""

   ## ABRE E OPERA O DIALOGO DE EDITAR/VISUALIZAR MATRIZ

"""


def abrir_editar():
    global direcionado
    global matriz_main
    layout_editar = gerar_layout('editar')
    window_editar = sg.Window('Editar/visualizar matriz',
                              layout_editar,
                              font='Arial 16',
                              element_justification="center",
                              auto_size_buttons=True,
                              grab_anywhere=True)
    while True:
        event, values = window_editar.read()
        if event == 'addVert':
            tamanho = len(matriz_main)
            novo_array = [i-i for i in range(len(matriz_main) + 1)]
            for i in matriz_main:
                i.append(0)
            matriz_main.append(novo_array)
            layout_editar = gerar_layout('editar')
            window_editar.close()
            window_editar = sg.Window('Editar/visualizar matriz',
                                      layout_editar,
                                      font='Arial 16',
                                      element_justification="center",
                                      auto_size_buttons=True,
                                      grab_anywhere=True)

        elif event == 'remVert':
            text = processar_input_vertice()
            if text != '':
                for i in range(len(matriz_main)):
                    matriz_main[i].pop(text)
                matriz_main.pop(text)
            layout_editar = gerar_layout('editar')
            window_editar.close()
            window_editar = sg.Window('Editar/visualizar matriz',
                                      layout_editar,
                                      font='Arial 16',
                                      element_justification="center",
                                      auto_size_buttons=True,
                                      auto_size_text=True,
                                      no_titlebar = True,
                                      grab_anywhere=True)

        elif event == 'conIncid':
            window_editar.close()
            layout_incidencia = gerar_layout('incidencia')
            window_incid = sg.Window('Visualizar matriz incidência',
                                  layout_incidencia,
                                  font='Arial 16',
                                  element_justification="center",
                                  auto_size_buttons=True,
                                  auto_size_text=True)
            event2, values2 = window_incid.read(close=True)
            if event2 is None or event2 == 'fecharIncid':
                window_incid.close()

        elif event == 'salvarEditar':
            tam_max = ceil(log(len(matriz_main)))
            for i in range(len(matriz_main)):
                for j in range(len(matriz_main[i])):
                    matriz_main[i][j] = int(values[str(i).zfill(tam_max) + str(j).zfill(tam_max)])
            sg.Popup("Salvo com sucesso!")
            window_editar.close()
            break
        elif event == 'fecharEditar' or event is None:
            window_editar.close()
            break


"""

   ## CALCULA O GRAU DO NO INFORMADO

"""


def calcular_grau_no(mostraresultado, no):
    global direcionado
    text = no
    if mostraresultado:
        text = processar_input_vertice()
    if text == '':
        return
    if not direcionado:
        grau = 0
        for i in range(len(matriz_main)):
            if matriz_main[i][text] > 0:
                grau = grau + matriz_main[i][text]
        if mostraresultado:
            sg.PopupOK('O grau do vértice informado é: ' + str(grau))
            return
        else:
            return grau
    else:
        grau_entrada = 0
        grau_saida = 0
        # Primeiro contando os graus de saida
        for i in range(len(matriz_main)):
            if matriz_main[i][text] > 0:
                grau_entrada += 1
            if matriz_main[text][i] > 0:
                grau_saida += 1
        if mostraresultado:
            sg.PopupOK('Grau de entrada: ' + str(grau_entrada) + '\n' + 'Grau de saída: ' + str(grau_saida) + '\n')
            return
        else:
            return grau_entrada


"""

   ## CARREGA O ARQUIVO INFORMADO NO MENU PRINCIPAL PRA DENTRO DO PROGRAMA

"""


def carregar_arquivo(path):
    if not path.endswith('txt'):
        sg.Popup("Erro, extensão de arquivo inválida.")
        return 0
    file = open(path, 'r')
    global matriz_main
    matriz_main = []
    comeca_em_zero = False
    count = 0
    for line in file.readlines():
        if line != '':
            count += 1
    matriz_main = [[i-i for i in range(count)] for j in range(count)]
    file.seek(0)
    for line in file.readlines():
        line = line.replace('\n', '')
        key = line.split(':')[0]
        items = line.split(':')[1].split(' ')
        if int(key) == 0:
            comeca_em_zero = True
        if int(key) != 0 and not comeca_em_zero:
            key = str(int(key-1))
        for i in items:
            if(i == ''):
                continue
            matriz_main[int(key)][int(i)] = 1

    sg.Popup("Importada com sucesso!")
    return 1


"""

   ## CONVERTE UMA MATRIZ DE ADJACÊNCIA EM UMA DE INCIDÊNCIA

"""


def converter_matriz(formato):
    global matriz_main
    global direcionado
    retorno = []
    if formato == 'incidencia':
        linha = [i-i for i in range(len(matriz_main))]
        retorno = [linha]
        current = 0
        ultimo = 0
        if not direcionado:
            for i in range(len(matriz_main)):
                for j in range(ultimo, len(matriz_main[i])):
                    if matriz_main[i][j] > 0:
                        if current+1 > len(retorno):
                            retorno.append([k-k for k in range(len(matriz_main))])
                        retorno[current][i] += 1
                        retorno[current][j] += 1
                        current += 1
                ultimo += 1
        else:
            for i in range(len(matriz_main)):
                for j in range(ultimo, len(matriz_main[i])):
                    if matriz_main[i][j] > 0:
                        if current+1 > len(retorno):
                            retorno.append([k-k for k in range(len(matriz_main))])
                        retorno[current][i] += 1
                        retorno[current][j] += -1
                        current += 1
                ultimo += 1
    elif formato == 'complemento':
        retorno = copy.deepcopy(matriz_main)
        for i in range(len(retorno)):
            for j in range(len(retorno[i])):
                if retorno[i][j] >= 1:
                    retorno[i][j] = 0
                else:
                    retorno[i][j] = 1
    return retorno



"""

   ## GERA UM LAYOUT PARA O PYSIMPLEGUI, DEPENDENDO DO CONTEXTO

"""


def gerar_layout(formato):
    global direcionado
    if formato == 'editar':
        tam_max = ceil(log(len(matriz_main)))
        headings = [str(data).zfill(tam_max) for data in range(len(matriz_main))]
        header = [[sg.Text(h, size=(tam_max, 1), justification='center', pad=(7, 1), text_color='red') for h in headings]]
        header[0].insert(0, sg.Text('     '))
        tam_max = ceil(log(len(matriz_main)))
        header_linha_row = [[sg.Text(h, size=(tam_max, 1), justification='center', pad=(7, 1), text_color='red')] for h in headings]
        input_rows = [[sg.Input(str(matriz_main[row][col]),
                       size=(tam_max+1, 1),
                       pad=(1, 1),
                       justification='center',
                       key=str(row).zfill(tam_max)+str(col).zfill(tam_max))
                       for col in range(len(headings))] for row in range(len(headings))]
        for i in range(len(input_rows)):
            input_rows[i].insert(0, header_linha_row[i][0])
        layout_retornar = header + input_rows
        layout_retornar.append([sg.Button("Adicionar vértice", key='addVert'),
        sg.Button("Remover Vértice", key='remVert')])
        layout_retornar.append([sg.Button("Converter incidência", key='conIncid'),
        sg.Button("Salvar", key='salvarEditar'),
        sg.Button("Fechar", key='fecharEditar')])
        return layout_retornar
    elif formato == 'complemento':
        matriz_compl = list(converter_matriz('complemento'))
        tam_max = ceil(log(len(matriz_compl)))
        headings = [' ' + str(data).zfill(tam_max) for data in range(len(matriz_compl))]
        header = [[]]
        for h in headings:
                header[0].append(sg.Text(h, size=(tam_max, 1), pad=(10, 1), text_color='red', justification='center'))
        header[0].insert(0, sg.Text('      '))
        header_linha_row = [[sg.Text('u' + str(h), size=(tam_max+1, 1), justification='center', pad=(7, 1), text_color='red')] for h in range(len(matriz_compl))]
        text_rows = [[sg.Input(' ' + str(matriz_compl[row][col]),
                              size=(tam_max+1, 1),
                              justification='center',
                              pad=(4, 1),
                              disabled=True,
                              key=str(row).zfill(tam_max)+str(col).zfill(tam_max)) for col in range(len(matriz_compl[row]))] for row in range(len(matriz_compl))]
        for i in range(len(text_rows)):
            text_rows[i].insert(0, header_linha_row[i][0])
        button = [[sg.Button("Fechar", key='fecharCompl')]]
        layout_retornar = header + text_rows + button
        return layout_retornar
    elif formato == 'incidencia':
        matriz_incid = converter_matriz('incidencia')
        tam_max = ceil(log(len(matriz_main)))
        headings = [' ' + str(data).zfill(tam_max) for data in range(len(matriz_main))]
        header = [[]]
        for h in headings:
                header[0].append(sg.Text(h, size=(tam_max, 1), pad=(10, 1), text_color='red', justification='center'))
        header[0].insert(0, sg.Text('      '))
        header_linha_row = [[sg.Text('u' + str(h), size=(tam_max+1, 1), justification='center', pad=(7, 1), text_color='red')] for h in range(len(matriz_main))]
        text_rows = [[sg.Input(' ' + str(matriz_main[row][col]),
                              size=(tam_max+1, 1),
                              justification='center',
                              pad=(4, 1),
                              disabled=True,
                              key=str(row).zfill(tam_max)+str(col).zfill(tam_max)) for col in range(len(matriz_incid[row]))] for row in range(len(matriz_incid))]
        for i in range(len(text_rows)):
            text_rows[i].insert(0, header_linha_row[i][0])
        button = [[sg.Button("Fechar", key='fecharIncid')]]
        layout_retornar = header + text_rows + button
        return layout_retornar


"""

   ## DIALOGO PARA RECEBER O NRO DE UM VERTICE

"""


def processar_input_vertice():
    event, values = sg.Window('Seleção vértice desejado',
                              [[sg.Text('Escolha o nro. do vértice desejado')],
                               [sg.Combo(list(range(len(matriz_main))), size=(3, 1))],
                               [sg.Button("Confirmar"),
                                sg.Button("Cancelar", key='cancelar')]
                              ],
                              font='Arial 16',
                              element_justification="center",
                              auto_size_buttons=True,
                              auto_size_text=True).read(close=True)
    if event == 'cancelar' or event is None:
        return ''
    try:
        text = int(values[0])
    except ValueError:
        sg.PopupError("Erro, número inválido digitado. Tente novamente.")
        return ''
    if text > len(matriz_main):
        sg.PopupError("Erro. Vértice não existe. Tente novamente.")
        return ''
    return text


"""

   ## TESTA SE A MATRIZ GLOBAL É DIRECIONADA

"""


def testar_direcionado():
    global matriz_main
    for i in range(len(matriz_main)):
        for j in range(len(matriz_main)):
            if matriz_main[i][j] != matriz_main[j][i]:
                return True
    return False


"""

   ## TESTA SE A MATRIZ GLOBAL É DIRECIONADA

"""


def testar_conexo(matriz):
    desconexo = False
    i = 0
    j = 0
    aux = []
    aux2 = []
    for i in range(len(matriz)):
        aux.append(0)
        aux2.append(-1)
    i = 0
    aux[0] = 1
    while True:
        a = matriz[i][j]
        if a > 0 and aux[j] == 0:
            aux2[j] = i
            aux[j] = 1
            i, j = j, i
        elif j == len(matriz)-1:
            if aux2[i] == -1:
                break
            temp = i
            i = aux2[i]
            j = temp
        else:
            j = j + 1
    for i in range(len(matriz)):
        if aux[i] == 0:
            desconexo = True
            break
    return desconexo


main([])
