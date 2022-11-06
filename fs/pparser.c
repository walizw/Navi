/*
 * pparser.c - A simple path parser implementation. It's job is to turn paths
 * like "0:/apps/nl" into a linked list of elements including the first one,
 * its drive number "0", the folders before the file, in the previous example
 * just "apps" and finally the file name.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */
#include "pparser.h"

/*
 * Ensures `fname' is a valid formated path.
 */
static int
pparser_path_valid_format (const char *fname)
{
  // TODO: Support relative paths
  int len = strnlen (fname, NAVI_MAX_PATH);
  return (len >= 3 && isdigit (fname[0])
          && memcmp ((void *)&fname[1], ":/", 2) == 0);
}

/*
 * Gets the drive number of `path'
 */
static int
pparser_get_drive_by_path (const char **path)
{
  if (!pparser_path_valid_format (*path))
    return -EBADPATH;

  int no = tonumericdigit (*path[0]);

  // adds 3 bytes to skip drive number
  *path += 3;
  return no;
}

/*
 * Creates the root of a path.
 */
static struct path_root *
pparser_create_root (int drive_no)
{
  struct path_root *root = kzalloc (sizeof (struct path_root));
  root->drive_no = drive_no;
  root->first = 0x00;
  return root;
}

/*
 * Gets a part from a path.
 */
static const char *
pparser_get_path_part (const char **path)
{
  char *result_path_part = kzalloc (NAVI_MAX_PATH);
  int i = 0;
  while (**path != '/' && **path != 0x00)
    {
      result_path_part[i] = **path;
      *path += 1;
      i++;
    }

  if (**path == '/')
    {
      // skipds forward slash
      *path += 1;
    }

  if (i == 0)
    {
      kfree (result_path_part);
      result_path_part = 0x00;
    }

  return result_path_part;
}

/*
 * Parses a path part intro a `path_part' struct.
 */
struct path_part *
pparser_parse_path_part (struct path_part *last, const char **path)
{
  const char *part_str = pparser_get_path_part (path);
  if (!part_str)
    return 0x00;

  struct path_part *part = kzalloc (sizeof (struct path_part));
  part->part = part_str;
  part->next = 0x00;

  if (last)
    {
      last->next = part;
    }

  return part;
}

/*
 * Frees a parsed path.
 */
void
pparser_free (struct path_root *root)
{
  struct path_part *part = root->first;
  while (part)
    {
      struct path_part *next = part->next;
      kfree ((void *)part->part);
      kfree (part);
      part = next;
    }

  kfree (root);
}

/*
 * Parses a path into a `path_root' structure.
 */
struct path_root *
pparser_parse (const char *path, const char *current)
{
  // TODO: Handle relative directories with `current'
  int res = 0;
  const char *tmp = path;
  struct path_root *root = 0x00;

  if (strlen (path) > NAVI_MAX_PATH)
    {
      goto out;
    }

  res = pparser_get_drive_by_path (&tmp);
  if (res < 0)
    goto out;

  root = pparser_create_root (res);
  if (!root)
    goto out;

  struct path_part *first = pparser_parse_path_part (0x00, &tmp);
  if (!first)
    goto out;

  root->first = first;
  struct path_part *part = pparser_parse_path_part (first, &tmp);
  while (part)
    {
      part = pparser_parse_path_part (part, &tmp);
    }

out:
  return root;
}
