#include "consultorio.h"
#include <stdio.h>

int main() {
  UsuarioNode *listaUsuarios = NULL;
  ConsultaNode *listaConsultas = NULL;

  printf("=== Cadastro de Usuário ===\n");
  cadastrarUsuario(&listaUsuarios);

  while (!realizarLogin(listaUsuarios))
    ;

  menu();

  int opcao;
  do {
    printf("Escolha uma opção do menu: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      agendarConsulta(&listaConsultas);
      break;
    case 2:
      listarConsultas(listaConsultas);
      break;
    case 3:
      buscarConsultaPorPaciente(listaConsultas);
      break;
    case 4:
      cancelarAgendamento(&listaConsultas);
      break;
    case 5:
      historicoAgendamentoPaciente(listaConsultas);
      break;
    case 6:
      editarConsultaAgendada(listaConsultas);
      break;
    case 7:
      ordenarConsultasPorData(&listaConsultas);
      break;
    case 0:
      printf("Programa encerrado!\n");
      break;
    default:
      printf("Opção inválida! Tente novamente.\n");
    }
  } while (opcao != 0);

  liberarListaUsuarios(listaUsuarios);
  liberarListaConsultas(listaConsultas);

  return 0;
}
