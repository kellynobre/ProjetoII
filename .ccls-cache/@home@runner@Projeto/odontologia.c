#include "consultorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct UsuarioNode {
  Usuario usuario;
  struct UsuarioNode *proximo;
} UsuarioNode;

typedef struct ConsultaNode {
  Consulta consulta;
  struct ConsultaNode *proximo;
} ConsultaNode;

void inserirUsuario(UsuarioNode **lista, Usuario usuario) {
  UsuarioNode *novoUsuario = (UsuarioNode *)malloc(sizeof(UsuarioNode));
  novoUsuario->usuario = usuario;
  novoUsuario->proximo = *lista;
  *lista = novoUsuario;
}

void liberarListaUsuarios(UsuarioNode *lista) {
  while (lista != NULL) {
    UsuarioNode *proximo = lista->proximo;
    free(lista);
    lista = proximo;
  }
}

void inserirConsulta(ConsultaNode **lista, Consulta consulta) {
  ConsultaNode *novaConsulta = (ConsultaNode *)malloc(sizeof(ConsultaNode));
  novaConsulta->consulta = consulta;
  novaConsulta->proximo = *lista;
  *lista = novaConsulta;
}

void liberarListaConsultas(ConsultaNode *lista) {
  while (lista != NULL) {
    ConsultaNode *proximo = lista->proximo;
    free(lista);
    lista = proximo;
  }
}

bool realizarLogin(UsuarioNode *listaUsuarios) {
  char nomeUsuarioDigitado[50];
  char senhaDigitada[50];

  printf("Digite seu nome de usuário: ");
  scanf("%s", nomeUsuarioDigitado);
  printf("Digite sua senha: ");
  scanf("%s", senhaDigitada);

  UsuarioNode *atual = listaUsuarios;
  while (atual != NULL) {
    if (strcmp(atual->usuario.nomeUsuario, nomeUsuarioDigitado) == 0 &&
        strcmp(atual->usuario.senha, senhaDigitada) == 0) {
      printf("Login bem-sucedido. Bem-vindo, %s!\n", nomeUsuarioDigitado);
      return true;
    }
    atual = atual->proximo;
  }

  printf("Nome de usuário ou senha incorretos. Tente novamente.\n");
  return false;
}

bool verificarEmail(char email[], UsuarioNode *listaUsuarios) {
  if (strlen(email) < 80 && strchr(email, '@') != NULL) {
    UsuarioNode *atual = listaUsuarios;
    while (atual != NULL) {
      if (strcmp(atual->usuario.email, email) == 0) {
        printf("Este e-mail já está cadastrado no sistema.\n");
        return false;
      }
      atual = atual->proximo;
    }
    printf("E-mail válido e não cadastrado anteriormente.\n");
    return true;
  } else {
    printf("E-mail inválido. Certifique-se de inserir um e-mail válido.\n");
    return false;
  }
}

void cadastrarUsuario(UsuarioNode **listaUsuarios) {
  Usuario novoUsuario;
  printf("Digite o nome de usuário: ");
  scanf("%s", novoUsuario.nomeUsuario);
  printf("Digite a senha: ");
  scanf("%s", novoUsuario.senha);
  printf("Digite o e-mail: ");
  scanf("%s", novoUsuario.email);

  while (!verificarEmail(novoUsuario.email, *listaUsuarios)) {
    printf("Digite o e-mail novamente: ");
    scanf("%s", novoUsuario.email);
  }

  inserirUsuario(listaUsuarios, novoUsuario);
  printf("Usuário cadastrado com sucesso!\n");
}

void menu() {
  printf("===================\n");
  printf("Bem-vindo à RY Odontologia!\n");
  printf("Nós nos dedicamos ao cuidado da sua saúde bucal e ao seu belo "
         "sorriso.\n");
  printf("===================\n");
  printf("Aqui estão as opções disponíveis:\n");
  printf("1 - Agendar uma consulta\n");
  printf("2 - Listar consultas agendadas\n");
  printf("3 - Buscar consulta por paciente\n");
  printf("4 - Cancelar agendamento\n");
  printf("5 - Histórico de agendamento do paciente\n");
  printf("6 - Editar consulta agendada\n");
  printf("7 - Ordenar consultas por data\n");
  printf("0 - Sair\n");
  printf("===================\n");
}

void agendarConsulta(ConsultaNode **listaConsultas) {
  Consulta novaConsulta;
  printf("Digite o nome do paciente: ");
  scanf("%s", novaConsulta.paciente);
  printf("Digite o telefone do paciente: ");
  scanf("%s", novaConsulta.telefone);
  printf("Digite a data desejada da consulta (formato DD/MM/AAAA): ");
  scanf("%s", novaConsulta.data);
  printf("Digite o procedimento a ser realizado: ");
  scanf("%s", novaConsulta.procedimento);
  inserirConsulta(listaConsultas, novaConsulta);
  printf("Consulta agendada com sucesso, em breve entraremos em contato!\n");
}

void listarConsultas(ConsultaNode *listaConsultas) {
  printf("Lista de consultas agendadas:\n");
  ConsultaNode *atual = listaConsultas;
  while (atual != NULL) {
    printf("Paciente: %s | Telefone: %s | Data: %s | Procedimento: %s\n",
           atual->consulta.paciente, atual->consulta.telefone,
           atual->consulta.data, atual->consulta.procedimento);
    atual = atual->proximo;
  }
}

void buscarConsultaPorPaciente(ConsultaNode *listaConsultas) {
  char nomePaciente[50];
  printf("Digite o nome do paciente: ");
  scanf("%s", nomePaciente);
  ConsultaNode *atual = listaConsultas;
  bool encontrou = false;
  while (atual != NULL) {
    if (strcmp(atual->consulta.paciente, nomePaciente) == 0) {
      printf("Paciente: %s | Telefone: %s | Data: %s | Procedimento: %s\n",
             atual->consulta.paciente, atual->consulta.telefone,
             atual->consulta.data, atual->consulta.procedimento);
      encontrou = true;
    }
    atual = atual->proximo;
  }
  if (!encontrou) {
    printf("Nenhuma consulta encontrada para o paciente: %s\n", nomePaciente);
  }
}

void cancelarAgendamento(ConsultaNode **listaConsultas) {
  char nomePaciente[50];
  printf("Digite o nome do paciente para cancelar o agendamento: ");
  scanf("%s", nomePaciente);
  ConsultaNode *atual = *listaConsultas;
  ConsultaNode *anterior = NULL;
  bool encontrou = false;
  while (atual != NULL) {
    if (strcmp(atual->consulta.paciente, nomePaciente) == 0) {
      if (anterior == NULL) {
        *listaConsultas = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }
      free(atual);
      printf("Agendamento para o paciente: %s cancelado com sucesso!\n",
             nomePaciente);
      encontrou = true;
      return;
    }
    anterior = atual;
    atual = atual->proximo;
  }
  if (!encontrou) {
    printf("Nenhuma consulta encontrada para o paciente: %s\n", nomePaciente);
  }
}

void editarConsultaAgendada(ConsultaNode *listaConsultas) {
  char nomePaciente[50];
  printf("Digite o nome do paciente para editar a consulta: ");
  scanf("%s", nomePaciente);
  ConsultaNode *atual = listaConsultas;
  bool encontrou = false;
  while (atual != NULL) {
    if (strcmp(atual->consulta.paciente, nomePaciente) == 0) {
      printf("Digite a nova data desejada da consulta (formato DD/MM/AAAA): ");
      scanf("%s", atual->consulta.data);
      printf("Digite o novo procedimento a ser realizado: ");
      scanf("%s", atual->consulta.procedimento);
      printf("Consulta editada com sucesso!\n");
      encontrou = true;
    }
    atual = atual->proximo;
  }
  if (!encontrou) {
    printf("Nenhuma consulta encontrada para o paciente: %s\n", nomePaciente);
  }
}

void historicoAgendamentoPaciente(ConsultaNode *listaConsultas) {
  char nomePaciente[50];
  printf("Digite o nome do paciente para visualizar o histórico de "
         "agendamentos: ");
  scanf("%s", nomePaciente);
  printf("Histórico de agendamentos para o paciente %s:\n", nomePaciente);
  ConsultaNode *atual = listaConsultas;
  bool encontrou = false;
  while (atual != NULL) {
    if (strcmp(atual->consulta.paciente, nomePaciente) == 0) {
      printf("Data: %s | Procedimento: %s\n", atual->consulta.data,
             atual->consulta.procedimento);
      encontrou = true;
    }
    atual = atual->proximo;
  }
  if (!encontrou) {
    printf("Nenhum agendamento encontrado para o paciente: %s\n", nomePaciente);
  }
}

void ordenarConsultasPorData(ConsultaNode **listaConsultas) {
  ConsultaNode *atual = *listaConsultas;
  ConsultaNode *anterior = NULL;
  ConsultaNode *temp;
  bool trocou;
  do {
    trocou = false;
    atual = *listaConsultas;
    while (atual->proximo != NULL) {
      if (strcmp(atual->consulta.data, atual->proximo->consulta.data) > 0) {
        if (anterior != NULL) {
          anterior->proximo = atual->proximo;
        } else {
          *listaConsultas = atual->proximo;
        }
        temp = atual->proximo->proximo;
        atual->proximo->proximo = atual;
        atual->proximo = temp;
        trocou = true;
      }
      anterior = atual;
      atual = atual->proximo;
    }
  } while (trocou);
  printf("Consultas ordenadas por data.\n");
}
