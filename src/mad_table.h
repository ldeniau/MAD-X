#ifndef MAD_TABLE_H
#define MAD_TABLE_H

// types

struct int_array;
struct char_p_array;

struct node;
struct in_cmd;
struct sequence;
struct name_list;
struct command_list;

struct table
{
  char name[NAME_L],
       type[NAME_L];            /* like "twiss", "survey" etc. */
  int  max,                     /* max. # rows */
       curr,                    /* current # rows */
       num_cols,                /* total # columns - fixed */
       org_cols,                /* original # columns from definition */
       dynamic,                 /* if != 0, values taken from current row */
       origin;                  /* 0 if created in job, 1 if read */
  struct char_p_array* header;  /* extra lines for file header */
  struct int_array* col_out;    /* column no.s to be written (in this order) */
  struct int_array* row_out;    /* flag for row: 1 write, 0 don't */
  struct char_p_array* node_nm; /* names of nodes at each row */
  struct char_p_array** l_head; /* extra lines to be put in front of a line */
  struct node** p_nodes;        /* pointers to nodes at each row */
  char*** s_cols;               /* string columns */
  double** d_cols;              /* double precision columns */
  int stamp;
  struct name_list* columns;    /* names + types (in inform):
                                   1 double, 3 string */
  struct sequence* org_sequ;    /* pointer to sequence it refers to */
};

struct table_list
{
  char name[NAME_L];
  int  max,                     /* max. pointer array size */
       curr;                    /* current occupation */
  struct name_list* names;      /* index list of tables */
  struct table** tables;
  int stamp;
};

struct table_list_list
{
  char name[NAME_L];
  int  max,                     /* max. pointer array size */
       curr;                    /* current occupation */
  struct table_list** table_lists;
  int stamp;
};

// interface

struct table*           make_table(char* name, char* type, char** table_cols, int* table_types, int rows);
struct table*           new_table(char* name, char* type, int rows, struct name_list* cols);
struct table_list*      new_table_list(int size);
struct table_list_list* new_table_list_list(int size);
struct table*           delete_table(struct table*);
struct table*           read_table(struct in_cmd*);
struct table*           read_my_table(struct in_cmd*);

void    check_table(char* string);
void    check_tabstring(char* string);
double  table_value(void);
void    add_to_table_list(struct table*, struct table_list*);
void    add_vars_to_table(struct table*);
void    set_vars_from_table(struct table*);
void    double_table(char* table);
void    grow_table(struct table*); /* doubles number of rows */
void    print_table(struct table*);
void    make_map_table(int* map_table_max_rows);
int     get_table_range(char* range, struct table*, int* rows);
void    headvalue(char* table_name, char* par, double* value);
void    out_table(char* tname, struct table*, char* filename);
void    reset_count(char* table); /* resets table counter to zero */
int     str_from_table(char* table, char* name, int* row, char* val);
int     str_from_tablet(struct table*, char* name, int* row, char* val);
void    sector_out(char* sector_table_name, double* pos, double* kick, double* rmatrix, double* tmatrix);
int     table_length(char* table);
void    table_range(char* table, char* range, int* rows);
void    string_to_table(char* table, char* name, char* string);
void    vector_to_table(char* table, char* col, int* nval, double* vals);

void    augment_count(char* table);
void    augmentcountonly(char* table);
int     char_from_table(char* table, char* name, int* row, char* val);
void    comment_to_table(char* table, char* comment, int* length);
void    double_to_table(char* table, char* name, double* val);
void    double_to_table_row(char* table, char* name, int* row, double* val);
int     double_from_table(char* table, char* name, int* row, double* val);
int     string_from_table(char* table, char* name, int* row, char* string);

struct column_info{
  void* data;
  int length;
  char datatype;
  char datasize;
};

struct column_info  table_get_column(char* table_name,char* column_name);

#endif // MAD_TABLE_H

