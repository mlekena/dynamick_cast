#ifndef EPISODE_HPP
#define EPISODE_HPP

#include <fstream>
#include <iostream>
#include <mutex>

#include <QModelIndex>
#include <QStandardItemModel>
#include <QString>

#include <boost/property_tree/ptree.hpp>
#include <pugixml.hpp>

#include "download_shared_state.hpp"
#include "string_functions.hpp"

class episode
{
public:
    episode() = delete;
    explicit episode(size_t item_number, pugi::xml_node::iterator iterator);

    const std::string &url() const;
    std::shared_ptr<download_shared_state> get_download_rights();
    QString get_title() const;
    bool has_title(const QString &text) const;
    void populate(int row, QStandardItemModel *model, std::string directory) const;
    void populate_download_progress(int row, QStandardItemModel *model) const;
    void serialize_into(std::ofstream &file);


protected:
    void fill(pugi::xml_node::iterator iterator);


    // The following two are left in but as is are dead code. ptree seems finicky and randomly
    // fails to parse xml that the pugi library succeeds with, however if you really want one less
    // dependency you can modify the calls in MainWindow::fetch_rss() to use them again.
    //
    // [5-Oct-2019] At some point I will replace this with a build option. I've tried to overhaul it twice with
    // template magic. Each time I broke the code badly enough that I want to think about it more before I try again.
    void fill(boost::property_tree::ptree::iterator tree_node);
public: explicit episode(size_t item_number, boost::property_tree::ptree::iterator tree_node);

private:
    std::string audio_url;
    std::size_t item_number_in_xml;
    QString description;
    QString guid;
    std::string page_url;
    QString publication_date;
    QString subtitle;
    QString title;
    mutable std::shared_ptr<download_shared_state> shared_state;
};

#endif // EPISODE_HPP
