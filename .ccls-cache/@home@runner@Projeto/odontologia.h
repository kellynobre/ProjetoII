#ifndef CONSULTORIO_H
#define CONSULTORIO_H

#include <stdbool.h>

typedef struct {
  char nomeUsuario[50];
  char senha[50];
  char email[80];
} Usuario;

typedef struct {
  char paciente[50];
  char telefone[20];
  char data[20];
  char procedimento[50];
} Consulta;

void inserirUsuario(UsuarioNode **lista, Usuario usuario);
void liberarListaUsuarios(UsuarioNode *lista);
void inserirConsulta(ConsultaNode **lista, Consulta consulta);
void liberarListaConsultas(ConsultaNode *lista);
bool realizarLogin(UsuarioNode *listaUsuarios);
bool verificarEmail(char email[], UsuarioNode *listaUsuarios);
void cadastrarUsuario(UsuarioNode **listaUsuarios);
void menu();
void agendarConsulta(ConsultaNode **listaConsultas);
void listarConsultas(ConsultaNode *listaConsultas);
void buscarConsultaPorPaciente(ConsultaNode *listaConsultas);
void cancelarAgendamento(ConsultaNode **listaConsultas);
void editarConsultaAgendada(ConsultaNode *listaConsultas);
void historicoAgendamentoPaciente(ConsultaNode *listaConsultas);
void ordenarConsultasPorData(ConsultaNode **listaConsultas);

#endif
