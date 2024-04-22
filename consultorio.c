#include "consultorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  FILE *arquivo;
  Usuario novoUsuario;
  char continuar;

  do {
    arquivo = fopen("usuarios.dat", "ab");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo de usuários.\n");
      return;
    }

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

    fwrite(&novoUsuario, sizeof(Usuario), 1, arquivo);
    fclose(arquivo);

    inserirUsuario(listaUsuarios, novoUsuario);
    printf("Usuário cadastrado com sucesso!\n");

    printf("Deseja cadastrar outro usuário? (S/N): ");
    scanf(" %c", &continuar);
  } while (continuar == 'S' || continuar == 's');
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
  FILE *arquivo;
  Consulta novaConsulta;

  arquivo = fopen("consultas.dat", "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de consultas.\n");
    return;
  }

  printf("Digite o nome do paciente: ");
  scanf("%s", novaConsulta.paciente);
  printf("Digite o telefone do paciente: ");
  scanf("%s", novaConsulta.telefone);
  printf("Digite a data desejada da consulta (formato DD/MM/AAAA): ");
  scanf("%s", novaConsulta.data);
  printf("Digite o procedimento a ser realizado: ");
  scanf("%s", novaConsulta.procedimento);

  fwrite(&novaConsulta, sizeof(Consulta), 1, arquivo);
  fclose(arquivo);

  inserirConsulta(listaConsultas, novaConsulta);
  printf("Consulta agendada com sucesso, em breve entraremos em contato!\n");
}

void listarConsultas(ConsultaNode *listaConsultas) {
  FILE *arquivo;
  Consulta consulta;

  arquivo = fopen("consultas.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de consultas.\n");
    return;
  }

  printf("Lista de consultas agendadas:\n");
  while (fread(&consulta, sizeof(Consulta), 1, arquivo) == 1) {
    printf("Paciente: %s | Telefone: %s | Data: %s | Procedimento: %s\n",
           consulta.paciente, consulta.telefone, consulta.data,
           consulta.procedimento);
  }

  fclose(arquivo);
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
  FILE *arquivo;
  Consulta consulta;
  char nomePaciente[50];
  bool encontrado = false;

  arquivo = fopen("consultas.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de consultas.\n");
    return;
  }

  FILE *temp;
  temp = fopen("temp.dat", "wb");

  printf("Digite o nome do paciente para cancelar o agendamento: ");
  scanf("%s", nomePaciente);

  while (fread(&consulta, sizeof(Consulta), 1, arquivo) == 1) {
    if (strcmp(consulta.paciente, nomePaciente) == 0) {
      printf("Agendamento para o paciente: %s cancelado com sucesso!\n",
             nomePaciente);
      encontrado = true;
    } else {
      fwrite(&consulta, sizeof(Consulta), 1, temp);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("consultas.dat");
  rename("temp.dat", "consultas.dat");

  if (!encontrado) {
    printf("Nenhuma consulta encontrada para o paciente: %s\n", nomePaciente);
  }
}

void editarConsultaAgendada(ConsultaNode *listaConsultas) {
  FILE *arquivo;
  Consulta consulta;
  char nomePaciente[50];
  char novaData[20];
  char novoProcedimento[50];
  bool encontrado = false;

  arquivo = fopen("consultas.dat", "rb+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de consultas.\n");
    return;
  }

  printf("Digite o nome do paciente para editar a consulta: ");
  scanf("%s", nomePaciente);

  while (fread(&consulta, sizeof(Consulta), 1, arquivo) == 1) {
    if (strcmp(consulta.paciente, nomePaciente) == 0) {
      printf("Digite a nova data desejada da consulta (formato DD/MM/AAAA): ");
      scanf("%s", novaData);
      printf("Digite o novo procedimento a ser realizado: ");
      scanf("%s", novoProcedimento);
      strcpy(consulta.data, novaData);
      strcpy(consulta.procedimento, novoProcedimento);
      fseek(arquivo, -sizeof(Consulta), SEEK_CUR);
      fwrite(&consulta, sizeof(Consulta), 1, arquivo);
      printf("Consulta editada com sucesso!\n");
      encontrado = true;
      break;
    }
  }

  fclose(arquivo);

  if (!encontrado) {
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
    anterior = NULL; // Resetar o ponteiro anterior no início de cada iteração
    while (atual != NULL && atual->proximo != NULL) {
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
      if (!trocou) {
        // Atualizar o ponteiro anterior apenas se não houve troca nesta
        // iteração
        anterior = atual;
      }
      atual = atual->proximo;
    }
  } while (trocou);

  // Após a ordenação, exibir a lista de consultas ordenadas
  printf("Consultas ordenadas por data:\n");
  ConsultaNode *cursor = *listaConsultas;
  while (cursor != NULL) {
    printf("Data: %s, Paciente: %s\n", cursor->consulta.data,
           cursor->consulta.paciente);
    cursor = cursor->proximo;
  }
}
