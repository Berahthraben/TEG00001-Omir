import PySimpleGUI as sg

sg.theme('Dark Blue')
headings = ['1', '2']
header = [[sg.Text(' ' + h, size=(2, 1)) for h in headings]]
input_rows = [[sg.Input(size=(3,1), pad=(1, 1)) for col in range(2)] for row in range(2)]
layout = [[sg.Text('Importar grafo de um arquivo')],
          [sg.Input('Caminho absoluto do arquivo'), sg.FileBrowse()],
          [sg.Text('Nome arquivo:'),
           sg.Text('N/D', key='nomeArq'),
           sg.Text('Direcionado:'),
           sg.Text('N/D', key='isDirecionado'),
           sg.Text('Incid. ou Adjac.:'),
           sg.Text('N/D', key='incidAdjac')],
          [sg.Button("Grau de nó"), sg.Button("Matriz do complemento (IN PROGRESS)")]]
layout += header + input_rows
def main(args):
    window = sg.Window('Programa de grafos TEG0001 - Nicolas Ribeiro e Maísa', layout, font='Arial 12')
    event, values = window.read()
main([])