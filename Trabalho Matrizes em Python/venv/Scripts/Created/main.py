#!/usr/bin/env python
# -*- coding: utf-8 -*-
import PySimpleGUI as sg

sg.theme('Dark Blue 3')
matriz_main = []
headings = ['1', '2']
header = [[sg.Text(' ' + h, size=(2, 1)) for h in headings]]
input_rows = [[sg.Input(size=(3, 1), pad=(1, 1)) for col in range(2)] for row in range(2)]
layoutMain = [[sg.Text('Importar grafo de um arquivo')],
              [sg.Input(key='buscarArquivo', enable_events=True), sg.FileBrowse("Buscar", target='buscarArquivo')],
              [sg.Text('Nome arquivo:'),
               sg.Text('N/D', key='nomeArq'),
               sg.Text('Direcionado:'),
               sg.Text('N/D', key='isDirecionado'),
               sg.Text('Incid. ou Adjac.:'),
               sg.Text('N/D', key='incidAdjac')],
              [sg.Button("Grau de vértice", key='grauNo'), sg.Button("Matriz do complemento (IN PROGRESS)")],
              [sg.Button("Visualizar/Editar matriz adjacência", key='abrirEditar')]]


def main(args):
    window_main = sg.Window('Programa de grafos TEG0001 - Nicolas Ribeiro e Maísa',
                            layoutMain,
                            font='Arial 16',
                            element_justification="center",
                            auto_size_buttons=True,
                            auto_size_text=True)
    while True:
        event, values = window_main.read()
        if event == 'grauNo':
            calcular_grau_no()
        elif event == 'abrirEditar':
            abrir_editar()
        elif event == 'buscarArquivo':
            matriz_main = carregar_arquivo(values['buscarArquivo'])
        elif event == None:
            break
            
                

def carregar_arquivo(path):
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
        print(line, key, items)
        if int(key) == 0:
            comeca_em_zero = True
        if int(key) != 0 and not comeca_em_zero:
            key = str(int(key-1))
        for i in items:
            if(i == ''):
                continue
            matriz_main[int(key)][int(i)] = 1
            """try :
                len(matriz_main[int(key)])
            except: 
                matriz_main.insert(int(key), [])
            try: 
                len(matriz_main[int(key)][int(item)])         
            except:
                matriz_main[int(key)].insert(int(item), 1)"""
    print(matriz_main)
    
def abrir_editar():
                
    layout_editar = gerar_layout('editar')
    window_editar = sg.Window('Editar/visualizar matriz',
                              layout_editar,
                              font='Arial 16',
                              element_justification="center",
                              auto_size_buttons=True,
                              auto_size_text=True)
    fechar = True
    while True:
        event, values = window_editar.read(close=fechar)
        fechar = True
        if event == 'addVert':
            tamanho = len(matriz_main)
            novo_array = [i-i for i in range(len(matriz_main) + 1)]
            for i in matriz_main:
                i.append(0)
            matriz_main.append(novo_array)
            layout_editar = gerar_layout('editar')
            window_editar = sg.Window('Editar/visualizar matriz',
                                      layout_editar,
                                      font='Arial 16',
                                      element_justification="center",
                                      auto_size_buttons=True,
                                      auto_size_text=True)
        elif event == 'remVert':
            text = processar_input_vertice()
            if text != '':
                for i in matriz_main:
                    i.pop(text-1)
                matriz_main.pop(text-1)
            layout_editar = gerar_layout('editar')
            window_editar = sg.Window('Editar/visualizar matriz',
                                      layout_editar,
                                      font='Arial 16',
                                      element_justification="center",
                                      auto_size_buttons=True,
                                      auto_size_text=True)
        elif event == 'salvarEditar':
            for i in range(len(matriz_main)):
                for j in range(len(matriz_main[i])):
                    matriz_main[i][j] = values[str(i) + str(j)]
                    
            sg.Popup("Salvo com sucesso!")
            break
        elif event == 'fecharEditar':
            break
                
                
def processar_input_vertice():
    event, values = sg.Window('Seleção vértice desejado',
                              [[sg.Text('Escolha o nro. do vértice desejado')],
                               [sg.Combo(list(range(1, len(matriz_main) + 1)), size=(3, 1))],
                               [sg.Button("Confirmar"),
                                sg.Button("Cancelar", key='cancelar')]
                              ],
                              font='Arial 16',
                              element_justification="center",
                              auto_size_buttons=True,
                              auto_size_text=True).read(close=True)
    if event == 'cancelar':
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


def gerar_layout(formato):
    if formato == 'editar':
        headings = [str(data) for data in range(1, len(matriz_main) + 1)]
        header = [[sg.Text(' ' + h, size=(2, 1), justification='center') for h in headings]]
        input_rows = [[sg.Input(str(matriz_main[row][col]), size=(3, 1), pad=(1, 1), key=str(row)+str(col)) for col in range(len(headings))] for row in range(len(headings))]
        layout_retornar = header + input_rows
        layout_retornar.append([sg.Button("Adicionar vértice", key='addVert'),
        sg.Button("Remover Vértice", key='remVert'),
        sg.Button("Salvar", key='salvarEditar'),
        sg.Button("Fechar", key='fecharEditar')])
        return layout_retornar

def calcular_grau_no():
    text = processar_input_vertice()
    if text == '':
        return
    grau = 0
    for i in range(len(matriz_main)):
        if matriz_main[i][text-1] > 0:
            grau += matriz_main[i][text-1]

    sg.Popup('O grau do vértice informado é: ' + str(grau))
    return  # garantir que encerra a execução. Não sei se precisa lol.


main([])
