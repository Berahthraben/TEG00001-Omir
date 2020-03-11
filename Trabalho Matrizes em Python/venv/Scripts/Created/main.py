#!/usr/bin/env python
# -*- coding: utf-8 -*-
import PySimpleGUI as sg
from math import log10 as log, ceil as ceil
import os

sg.theme('Dark Blue 3')
matriz_main = []
adjacencia = False
direcionado = False
headings = ['1', '2']
header = [[sg.Text(' ' + h, size=(2, 1)) for h in headings]]
input_rows = [[sg.Input(size=(3, 1), pad=(1, 1)) for col in range(2)] for row in range(2)]
layoutMain = [[sg.Text('Importar grafo de um arquivo')],
              [sg.Input(key='buscarArquivo', enable_events=True), sg.FileBrowse("Buscar", target='buscarArquivo')],
              [sg.Text('Direcionado:', font='Arial 12'),
               sg.Text('N/D', key='isDirecionado', font='Arial 12'),
               sg.Text('Incid. ou Adjac.:', font='Arial 12'),
               sg.Text('N/D', key='incidAdjac', font='Arial 12')],
              [sg.Button("Grau de vértice", key='grauNo'), sg.Button("Matriz do complemento (IN PROGRESS)")],
              [sg.Button("Visualizar/Editar matriz adjacência", key='abrirEditar')]]


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
        print(event, values)
        if event == 'grauNo':
            calcular_grau_no()
        elif event == 'abrirEditar':
            abrir_editar()
        elif event == 'buscarArquivo':
            sucesso = carregar_arquivo(values['buscarArquivo'])
            if sucesso == 1:
                direcionado = testar_direcionado()
                if direcionado:
                    window_main['isDirecionado'].update("Sim")
                else:
                    window_main['isDirecionado'].update("Não")
                
        elif event == None:
            break
            
                

def testar_direcionado():
    global matriz_main
    for i in range(len(matriz_main)):
        for j in range(len(matriz_main)):
            if(matriz_main[i][j] != matriz_main[j][i]):
                return True
    return False

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
    
def abrir_editar():
    global direcionado
    layout_editar = gerar_layout('editar')
    window_editar = sg.Window('Editar/visualizar matriz',
                              layout_editar,
                              font='Arial 16',
                              element_justification="center",
                              auto_size_buttons=True,
                              auto_size_text=True)
    fechar = False
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
        elif event == 'conIncid':
            fechar = False
            if direcionado :
                sg.Popup("Conversão de matriz de adj. direcionada p/ incidencia em progresso.")
            else:
                layout_incidencia = gerar_layout('incidencia')
                event2, values2 = sg.Window('Visualizar matriz incidência',
                                      layout_incidencia,
                                      font='Arial 16',
                                      element_justification="center",
                                      auto_size_buttons=True,
                                      auto_size_text=True).read(close=True)
            
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
        tam_max = ceil(log(len(matriz_main)))
        input_rows = [[sg.Input(str(matriz_main[row][col]),
                       size=(3, 1),
                       pad=(1, 1),
                       key=str(row).zfill(tam_max)+str(col).zfill(tam_max))
                       for col in range(len(headings))] for row in range(len(headings))]
        layout_retornar = header + input_rows
        layout_retornar.append([sg.Button("Adicionar vértice", key='addVert'),
        sg.Button("Remover Vértice", key='remVert'),
        sg.Button("Converter incidência", key='conIncid'),
        sg.Button("Salvar", key='salvarEditar'),
        sg.Button("Fechar", key='fecharEditar')])
        return layout_retornar
    elif formato == 'incidencia':
        matriz_incid = converter_matriz()
        tam_max = ceil(log(len(matriz_incid)))
        headings = [str(data) for data in range(1, len(matriz_incid) + 1)]
        header = [[]]
        for h in headings:
            if tam_max > 1:
                header[0].append(sg.Text(h.zfill(tam_max), size=(tam_max, 1), pad=(3, 1), text_color='red', justification='center'))
            else:
                header[0].append(sg.Text(h.zfill(tam_max), justification='center'))
        texto_linhas = ['u' + str(data) for data in range(1, len(matriz_incid) + 1)]
        header_linhas = [[sg.Text(texto_linhas[row],
                              size=(1, 1),
                              justification='center',
                              pad=(1, 1)) for row in range(len(matriz_incid))]]
        text_rows = [[sg.Text(' ' + str(matriz_incid[row][col]).zfill(tam_max),
                              size=(tam_max, 1),
                              justification='center',
                              pad=(3, 1),
                              key=str(row).zfill(tam_max)+str(col).zfill(tam_max)) for col in range(len(matriz_incid[row]))] for row in range(len(matriz_incid))]
        layout_retornar = header + text_rows
        return layout_retornar
        
def converter_matriz():
    global matriz_main
    linha = [i-i for i in range(len(matriz_main))]
    retorno = [linha]
    current = 0
    ultimo = 0
    for i in range(len(matriz_main)):
        for j in range(ultimo, len(matriz_main[i])):
            if matriz_main[i][j] > 0:
                if current+1 > len(retorno):
                    retorno.append([k-k for k in range(len(matriz_main))])
                retorno[current][i] += 1
                retorno[current][j] += 1
                current += 1
        ultimo += 1
    return retorno
    
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
