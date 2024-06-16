#include "include/mongoose.h"
#include "include/user.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define BIND "http://0.0.0.0:8000"

#define USER_COUNT 64
user_t users[USER_COUNT];
uint32_t user_index = 0;

#define RESPONSE_LENGTH 2048

void user_id_handler(struct mg_connection *c, struct mg_http_message *hm,
                     uint32_t id) {
  if (id >= user_index) {
    mg_http_reply(c, 404, "", "User not found.\n"); // not found
    return;
  }

  if (mg_strcmp(hm->method, mg_str("GET")) == 0) {
    char response[RESPONSE_LENGTH] = {0};
    const user_t *user = &users[id];
    snprintf(response, RESPONSE_LENGTH, "user { id: %d, name: %s, reg_date: %ld }\n",
             user->id, user->name, user->reg_date);

    mg_http_reply(c, 200, "", response); // method not allowed
  } else {
    mg_http_reply(c, 405, "", "Method not allowed.\n"); // method not allowed
  }
}

void user_handler(struct mg_connection *c, struct mg_http_message *hm) {
  if (mg_strcmp(hm->method, mg_str("POST")) == 0) {
    char *name = mg_json_get_str(hm->body, "$.name");
    if (name == NULL) {
      mg_http_reply(c, 400, "", "Name is null.\n"); // bad request
      return;
    }

    if (user_index >= USER_COUNT) {
      mg_http_reply(c, 403, "", "Maximum user count reached.\n"); // forbidden
      return;
    }

    time_t reg_date = time(NULL);

    users[user_index].id = user_index;
    users[user_index].name = name;
    users[user_index].reg_date = reg_date;
    user_index++;

    mg_http_reply(c, 200, "", "User created.\n");
  } else if (mg_strcmp(hm->method, mg_str("GET")) == 0) {
    char response[RESPONSE_LENGTH] = {0};
    int offset = 0;
    for (size_t i = 0; i < user_index && offset < RESPONSE_LENGTH; i++) {
      offset += snprintf(response + offset, RESPONSE_LENGTH - offset,
                         "user { id: %d, name: %s, reg_date: %ld }\n",
                         users[i].id, users[i].name, users[i].reg_date);
    }

    mg_http_reply(c, 200, "", response);
  } else {
    mg_http_reply(c, 405, "", "Method not allowed.\n"); // method not allowed
  }
}

// HTTP server event handler function
void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    struct mg_http_serve_opts opts = {.root_dir = "./web_root/"};

    struct mg_str params[1];

    if (mg_match(hm->uri, mg_str("/api/user"), NULL)) {
      user_handler(c, hm);
    } else if (mg_match(hm->uri, mg_str("/api/user/*"), params)) {
      uint32_t id;
      mg_str_to_num(params[0], 10, (void *)&id, sizeof(id));
      user_id_handler(c, hm, id);
    } else {
      mg_http_serve_dir(c, hm, &opts);
    }
  }
}

int main(void) {
  printf("starting...\n");
  fflush(stdout);
  struct mg_mgr mgr; // Declare event manager
  mg_mgr_init(&mgr); // Initialise event manager

  struct mg_connection *conn =
      mg_http_listen(&mgr, BIND, ev_handler, NULL); // Setup listener

  if (conn == NULL) {
    perror("mg_http_listen");
    return 1;
  }

  printf("started mongoose server at %s\n", BIND);
  fflush(stdout);

  for (;;) { // Run an infinite event loop
    mg_mgr_poll(&mgr, 1000);
  }

  return 0;
}
